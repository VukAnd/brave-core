/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <utility>

#include "base/strings/stringprintf.h"
#include "bat/ledger/internal/database/database_server_publisher_info.h"
#include "bat/ledger/internal/database/database_util.h"
#include "bat/ledger/internal/ledger_impl.h"

using std::placeholders::_1;

namespace {
  const char table_name_[] = "server_publisher_info";
}  // namespace

namespace braveledger_database {

DatabaseServerPublisherInfo::DatabaseServerPublisherInfo(
    bat_ledger::LedgerImpl* ledger) :
    DatabaseTable(ledger),
    banner_(std::make_unique<DatabaseServerPublisherBanner>(ledger)) {
}

DatabaseServerPublisherInfo::~DatabaseServerPublisherInfo() = default;

bool DatabaseServerPublisherInfo::CreateTableV7(
    ledger::DBTransaction* transaction) {
  const std::string query = base::StringPrintf(
      "CREATE TABLE %s "
      "("
      "publisher_key LONGVARCHAR PRIMARY KEY NOT NULL UNIQUE,"
      "status INTEGER DEFAULT 0 NOT NULL,"
      "excluded INTEGER DEFAULT 0 NOT NULL,"
      "address TEXT NOT NULL"
      ")",
      table_name_);

  auto command = ledger::DBCommand::New();
  command->type = ledger::DBCommand::Type::EXECUTE;
  command->command = query;
  transaction->commands.push_back(std::move(command));

  return true;
}

bool DatabaseServerPublisherInfo::CreateIndexV7(
    ledger::DBTransaction* transaction) {
  return this->InsertIndex(transaction, table_name_, "publisher_key");
}

bool DatabaseServerPublisherInfo::Migrate(
    ledger::DBTransaction* transaction,
    const int target) {
  if (!transaction) {
    return false;
  }

  switch (target) {
    case 7: {
      return MigrateToV7(transaction);
    }
    case 15: {
      return MigrateToV15(transaction);
    }
    default: {
      return true;
    }
  }
}

bool DatabaseServerPublisherInfo::MigrateToV7(
    ledger::DBTransaction* transaction) {
  if (!DropTable(transaction, table_name_)) {
    return false;
  }

  if (!CreateTableV7(transaction)) {
    return false;
  }

  if (!CreateIndexV7(transaction)) {
    return false;
  }

  if (!banner_->Migrate(transaction, 7)) {
    return false;
  }

  return true;
}

bool DatabaseServerPublisherInfo::MigrateToV15(
    ledger::DBTransaction* transaction) {
  return banner_->Migrate(transaction, 15);
}

void DatabaseServerPublisherInfo::InsertOrUpdate(
    ledger::DBTransaction* transaction,
    ledger::ServerPublisherInfoPtr info) {
  if (!info) {
    return;
  }

  const std::string query = base::StringPrintf(
      "INSERT OR REPLACE INTO %s "
      "(publisher_key, status, excluded, address) "
      "VALUES (?, ?, ?, ?)",
      table_name_);

  auto command = ledger::DBCommand::New();
  command->type = ledger::DBCommand::Type::RUN;
  command->command = query;

  BindString(command.get(), 0, info->publisher_key);
  BindInt(command.get(), 1, static_cast<int>(info->status));
  BindBool(command.get(), 2, info->excluded);
  BindString(command.get(), 3, info->address);

  transaction->commands.push_back(std::move(command));
}

void DatabaseServerPublisherInfo::ClearAndInsertList(
    const ledger::ServerPublisherInfoList& list,
    ledger::ResultCallback callback) {
  auto transaction_callback = std::bind(&OnResultCallback,
      _1,
      callback);
  auto transaction = ledger::DBTransaction::New();
  const std::string query = base::StringPrintf(
      "DELETE FROM %s",
      table_name_);

  auto command = ledger::DBCommand::New();
  command->type = ledger::DBCommand::Type::EXECUTE;
  command->command = query;
  transaction->commands.push_back(std::move(command));

  if (list.size() == 0) {
    ledger_->RunDBTransaction(std::move(transaction), transaction_callback);
    return;
  }

  for (const auto& info : list) {
    if (!info) {
      continue;
    }

    InsertOrUpdate(transaction.get(), info->Clone());

    if (info->banner) {
      banner_->InsertOrUpdate(transaction.get(), info->Clone());
    }
  }

  ledger_->RunDBTransaction(std::move(transaction), transaction_callback);
}

void DatabaseServerPublisherInfo::GetRecord(
    const std::string& publisher_key,
    ledger::GetServerPublisherInfoCallback callback) {
  // Get banner first as is not complex struct where ServerPublisherInfo is
  auto banner_callback =
      std::bind(&DatabaseServerPublisherInfo::OnGetRecordBanner,
          this,
          _1,
          publisher_key,
          callback);

  banner_->GetRecord(publisher_key, banner_callback);
}

void DatabaseServerPublisherInfo::OnGetRecordBanner(
    ledger::PublisherBannerPtr banner,
    const std::string& publisher_key,
    ledger::GetServerPublisherInfoCallback callback) {
  auto transaction = ledger::DBTransaction::New();
  const std::string query = base::StringPrintf(
      "SELECT status, excluded, address "
      "FROM %s WHERE publisher_key=?",
      table_name_);

  auto command = ledger::DBCommand::New();
  command->type = ledger::DBCommand::Type::READ;
  command->command = query;

  BindString(command.get(), 0, publisher_key);

  command->record_bindings = {
      ledger::DBCommand::RecordBindingType::INT_TYPE,
      ledger::DBCommand::RecordBindingType::BOOL_TYPE,
      ledger::DBCommand::RecordBindingType::STRING_TYPE
  };

  transaction->commands.push_back(std::move(command));

  if (!banner) {
    banner = ledger::PublisherBanner::New();
  }

  auto transaction_callback =
      std::bind(&DatabaseServerPublisherInfo::OnGetRecord,
          this,
          _1,
          publisher_key,
          *banner,
          callback);

  ledger_->RunDBTransaction(std::move(transaction), transaction_callback);
}

void DatabaseServerPublisherInfo::OnGetRecord(
    ledger::DBCommandResponsePtr response,
    const std::string& publisher_key,
    const ledger::PublisherBanner& banner,
    ledger::GetServerPublisherInfoCallback callback) {
  if (!response || response->status != ledger::DBCommandResponse::Status::OK) {
    callback(nullptr);
    return;
  }

  if (response->result->get_records().size() != 1) {
    callback(nullptr);
    return;
  }

  auto* record = response->result->get_records()[0].get();

  auto info = ledger::ServerPublisherInfo::New();
  info->publisher_key = publisher_key;
  info->status = static_cast<ledger::mojom::PublisherStatus>(
      GetIntColumn(record, 0));
  info->excluded = GetBoolColumn(record, 1);
  info->address = GetStringColumn(record, 2);
  info->banner = banner.Clone();

  callback(std::move(info));
}

}  // namespace braveledger_database