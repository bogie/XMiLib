﻿/// \file
/// \author 
///
/// \brief Implementation of string list editor dialog class
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#include "stdafx.h"
#include "StringListEditorDialog.h"
#include "Exception.h"
#include "XMiLibConstants.h"
#include "ui_StringListEditorDialog.h"


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] stringList The string list
/// \param[in] parent The parent widget of the dialog
//**********************************************************************************************************************
StringListEditorDialog::StringListEditorDialog(QStringList const& stringList, QWidget* parent)
   : QDialog(parent, constants::kDefaultDialogFlags)
   , ui_(new Ui::StringListEditorDialog)
   , model_(stringList)
{
   ui_->setupUi(this);
   lastActionButton_ = ui_->buttonRemove;
   ui_->stringListView->setModel(&model_);
   QItemSelectionModel const * const selModel = ui_->stringListView->selectionModel();
   if (selModel)
      connect(selModel, &QItemSelectionModel::selectionChanged, this, &StringListEditorDialog::onSelectionChanged);
   this->setHeaderText(QString());
   this->updateGui();
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
StringListEditorDialog::~StringListEditorDialog()  // NOLINT(hicpp-use-equals-default)
{
}


//**********************************************************************************************************************
/// \return The string list
//**********************************************************************************************************************
QStringList StringListEditorDialog::stringList() const
{
   return model_.stringList();
}


//**********************************************************************************************************************
/// \param[in] stringList The string list
//**********************************************************************************************************************
void StringListEditorDialog::setStringList(QStringList const& stringList)
{
   model_.setStringList(stringList);
}


//**********************************************************************************************************************
/// \param[in] text The text
//**********************************************************************************************************************
void StringListEditorDialog::setHeaderText(QString const& text) const
{
   ui_->labelHeader->setText(text);
   ui_->labelHeader->setVisible(!text.isEmpty());
}


//**********************************************************************************************************************
/// \param[in] button The button to add
//**********************************************************************************************************************
void StringListEditorDialog::addCustomButton(QPushButton* button)
{
   ui_->buttonLayout->addWidget(button);
   setTabOrder(lastActionButton_, button);
   setTabOrder(button, ui_->buttonOk);
   lastActionButton_ = button;
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void StringListEditorDialog::onActionAddString()
{
   try
   {
      qint32 const row = model_.rowCount();
      model_.insertRows(row, 1);
      QModelIndex const index = model_.index(row);
      ui_->stringListView->setCurrentIndex(index);
      ui_->stringListView->edit(index);
      this->updateGui();
   }
   catch (Exception const& e)
   {
      QMessageBox::critical(this, tr("Error"), tr("Internal error: %1").arg(e.qwhat()));
   }
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void StringListEditorDialog::onActionRemoveString()
{
   try
   {
      QItemSelectionModel const * const selModel = ui_->stringListView->selectionModel();
      if (!selModel)
         throw Exception(tr("Could not retrieve selection model."));
      QModelIndexList selection = selModel->selectedRows(); // we sort the select by descending column so that removal does not shift indexes
      std::sort(selection.begin(), selection.end(), [](QModelIndex const& a, QModelIndex const& b) -> bool 
         {return a.row() > b.row(); });
      for (QModelIndex const& index: selection)
         model_.removeRows(index.row(), 1);
      this->updateGui();
   }
   catch (Exception const& e)
   {
      QMessageBox::critical(this, tr("Error"), tr("Internal error: %1").arg(e.qwhat()));
   }
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void StringListEditorDialog::onSelectionChanged()
{
   this->updateGui();
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void StringListEditorDialog::updateGui()
{
   try
   {
      QItemSelectionModel const * const selModel = ui_->stringListView->selectionModel();
      if (!selModel)
         throw Exception(tr("Could not retrieve selection model."));
      qint32 const selectedRowCount = selModel->selectedRows().size();

      ui_->buttonRemove->setEnabled(selectedRowCount > 0);
   }
   catch (Exception const& e)
   {
      QMessageBox::critical(this, tr("Error"), tr("Internal error: %1").arg(e.qwhat()));
   }
}


} // namespace xmilib
