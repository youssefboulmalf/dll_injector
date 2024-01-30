#pragma once
#include "helper.h"

namespace dll_injector {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for mainForm
	/// </summary>
	public ref class mainForm : public System::Windows::Forms::Form
	{
	public:
		mainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~mainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ dllLable;
	private: System::Windows::Forms::Button^ selectFileButton;
	protected:


	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ dllTextBox;


	private: System::Windows::Forms::Button^ loadPIDs;
	private: System::Windows::Forms::Button^ injectionButton;



	private: System::Windows::Forms::CheckedListBox^ processCheckBoxList;
	private: System::Windows::Forms::OpenFileDialog^ openDllFile;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dllLable = (gcnew System::Windows::Forms::Label());
			this->selectFileButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->dllTextBox = (gcnew System::Windows::Forms::TextBox());
			this->loadPIDs = (gcnew System::Windows::Forms::Button());
			this->injectionButton = (gcnew System::Windows::Forms::Button());
			this->processCheckBoxList = (gcnew System::Windows::Forms::CheckedListBox());
			this->openDllFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// dllLable
			// 
			this->dllLable->AutoSize = true;
			this->dllLable->Location = System::Drawing::Point(31, 42);
			this->dllLable->Name = L"dllLable";
			this->dllLable->Size = System::Drawing::Size(164, 16);
			this->dllLable->TabIndex = 0;
			this->dllLable->Text = L"Choose dll file for injection:";
			// 
			// selectFileButton
			// 
			this->selectFileButton->Location = System::Drawing::Point(428, 80);
			this->selectFileButton->Name = L"selectFileButton";
			this->selectFileButton->Size = System::Drawing::Size(84, 23);
			this->selectFileButton->TabIndex = 2;
			this->selectFileButton->Text = L"Select file";
			this->selectFileButton->UseVisualStyleBackColor = true;
			this->selectFileButton->Click += gcnew System::EventHandler(this, &mainForm::selectFileClick);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(31, 152);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(125, 16);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Choose process ID:";
			// 
			// dllTextBox
			// 
			this->dllTextBox->Enabled = false;
			this->dllTextBox->Location = System::Drawing::Point(34, 80);
			this->dllTextBox->Name = L"dllTextBox";
			this->dllTextBox->Size = System::Drawing::Size(378, 22);
			this->dllTextBox->TabIndex = 4;
			// 
			// loadPIDs
			// 
			this->loadPIDs->Location = System::Drawing::Point(403, 283);
			this->loadPIDs->Name = L"loadPIDs";
			this->loadPIDs->Size = System::Drawing::Size(122, 23);
			this->loadPIDs->TabIndex = 6;
			this->loadPIDs->Text = L"Load Processes";
			this->loadPIDs->UseVisualStyleBackColor = true;
			this->loadPIDs->Click += gcnew System::EventHandler(this, &mainForm::loadPIDs_Click);
			// 
			// injectionButton
			// 
			this->injectionButton->Location = System::Drawing::Point(156, 429);
			this->injectionButton->Name = L"injectionButton";
			this->injectionButton->Size = System::Drawing::Size(213, 32);
			this->injectionButton->TabIndex = 7;
			this->injectionButton->Text = L"Inject";
			this->injectionButton->UseVisualStyleBackColor = true;
			this->injectionButton->Click += gcnew System::EventHandler(this, &mainForm::injectionButtonClick);
			// 
			// processCheckBoxList
			// 
			this->processCheckBoxList->CheckOnClick = true;
			this->processCheckBoxList->FormattingEnabled = true;
			this->processCheckBoxList->Location = System::Drawing::Point(34, 181);
			this->processCheckBoxList->Name = L"processCheckBoxList";
			this->processCheckBoxList->Size = System::Drawing::Size(363, 208);
			this->processCheckBoxList->TabIndex = 8;
			this->processCheckBoxList->SelectedIndexChanged += gcnew System::EventHandler(this, &mainForm::processCheckBoxList_SelectedIndexChanged);
			// 
			// openDllFile
			// 
			this->openDllFile->Filter = L"dll files (*.dll) |*.dll";
			this->openDllFile->InitialDirectory = L"c:\\\\";
			this->openDllFile->RestoreDirectory = true;
			// 
			// mainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(539, 485);
			this->Controls->Add(this->processCheckBoxList);
			this->Controls->Add(this->injectionButton);
			this->Controls->Add(this->loadPIDs);
			this->Controls->Add(this->dllTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->selectFileButton);
			this->Controls->Add(this->dllLable);
			this->Name = L"mainForm";
			this->Text = L"mainForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void loadPIDs_Click(System::Object^ sender, System::EventArgs^ e) {
		this->processCheckBoxList->Items->AddRange(EnumProcs());
	}
	private: System::Void processCheckBoxList_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		for (int i = 0; i < this->processCheckBoxList->Items->Count; ++i)
			if (processCheckBoxList->SelectedIndex!= i) processCheckBoxList->SetItemChecked(i, false);
	}
	private: System::Void selectFileClick(System::Object^ sender, System::EventArgs^ e) {		
		if (openDllFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			this->dllTextBox->Text = openDllFile->FileName;
		}

	}
	private: System::Void injectionButtonClick(System::Object^ sender, System::EventArgs^ e) {
		injectDll(this->dllTextBox->Text, this->processCheckBoxList->SelectedItem);
	}
};
}
