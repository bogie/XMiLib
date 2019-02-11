﻿/// \file
/// \author 
///
/// \brief Declaration of string list editor dialog class
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#ifndef XMILIB_STRING_LIST_EDITOR_DIALOG_H
#define XMILIB_STRING_LIST_EDITOR_DIALOG_H


#include "StringListEditorModel.h"


namespace Ui {


class StringListEditorDialog;


}

namespace xmilib {


//**********************************************************************************************************************
/// \brief String list editor dialog class
//**********************************************************************************************************************
class StringListEditorDialog: public QDialog
{
   Q_OBJECT
public: // member functions
   explicit StringListEditorDialog(QStringList const& stringList, QWidget* parent = nullptr); ///< Default constructor
   StringListEditorDialog(StringListEditorDialog const&) = delete; ///< Disabled copy-constructor
   StringListEditorDialog(StringListEditorDialog&&) = delete; ///< Disabled assignment copy-constructor
   ~StringListEditorDialog(); ///< Destructor
   StringListEditorDialog& operator=(StringListEditorDialog const&) = delete; ///< Disabled assignment operator
   StringListEditorDialog& operator=(StringListEditorDialog&&) = delete; ///< Disabled move assignment operator
   QStringList stringList() const; ///< Return the string list
   void setStringList(QStringList const& stringList); ///< Set the dialog's string list
   void setHeaderText(QString const& text) const; ///< Set the text to display in the dialog's header
   void addCustomButton(QPushButton* button); ///< Add a custom button to dialog

private slots:
   void onActionAddString(); ///< Slot for the 'Add string' action
   void onActionRemoveString(); ///< Slot for the 'Add string' action
   void onSelectionChanged(); ///< Slot for changes of the selection

private: // member function
   void updateGui(); ///< Update the GUI state

private: // data members
   std::unique_ptr<Ui::StringListEditorDialog> ui_ { nullptr }; ///< The GUI for the dialog
   StringListEditorModel model_; ///< The model used by the list view
   QPushButton* lastActionButton_ { nullptr }; ///< The last action button, used to ensure proper tab order when adding custom buttons
};


} // namespace xmilib


#endif // #ifndef XMILIB_STRING_LIST_EDITOR_DIALOG_H
