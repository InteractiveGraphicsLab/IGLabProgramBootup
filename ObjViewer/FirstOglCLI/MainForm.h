#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#pragma managed


namespace FirstOglCLI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MainForm の概要
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{

	private:
		OglForCLI* m_ogl;

	private: // 書き換え <-- コンストラクタをprivateにする
		MainForm(void);
	private: System::Windows::Forms::Label^ label1;
				 static MainForm^ m_singleton; // <--追加 nullptrで初期化されている

	public:
		static MainForm^ GetInst() // <--追加 シングルトンパターン
		{
			if (m_singleton == nullptr) m_singleton = gcnew MainForm();
			return m_singleton;
		}
		
		void RedrawPanel(); // <-- 追加

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ m_panel;
	private: System::Windows::Forms::Button^ m_button1;
	private: System::Windows::Forms::Button^ m_button2;


	protected:

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->m_panel = (gcnew System::Windows::Forms::Panel());
			this->m_button1 = (gcnew System::Windows::Forms::Button());
			this->m_button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// m_panel
			// 
			this->m_panel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_panel->Location = System::Drawing::Point(12, 12);
			this->m_panel->Name = L"m_panel";
			this->m_panel->Size = System::Drawing::Size(880, 822);
			this->m_panel->TabIndex = 0;
			this->m_panel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::m_panel_Paint);
			this->m_panel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::m_panel_MouseDown);
			this->m_panel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::m_panel_MouseMove);
			this->m_panel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::m_panel_MouseUp);
			this->m_panel->Resize += gcnew System::EventHandler(this, &MainForm::m_panel_Resize);
			// 
			// m_button1
			// 
			this->m_button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->m_button1->Location = System::Drawing::Point(12, 840);
			this->m_button1->Name = L"m_button1";
			this->m_button1->Size = System::Drawing::Size(103, 47);
			this->m_button1->TabIndex = 1;
			this->m_button1->Text = L"LoadObj";
			this->m_button1->UseVisualStyleBackColor = true;
			this->m_button1->Click += gcnew System::EventHandler(this, &MainForm::m_button1_Click);
			// 
			// m_button2
			// 
			this->m_button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->m_button2->Location = System::Drawing::Point(121, 840);
			this->m_button2->Name = L"m_button2";
			this->m_button2->Size = System::Drawing::Size(103, 47);
			this->m_button2->TabIndex = 2;
			this->m_button2->Text = L"SetMatrix (txt)";
			this->m_button2->UseVisualStyleBackColor = true;
			this->m_button2->Click += gcnew System::EventHandler(this, &MainForm::m_button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label1->Location = System::Drawing::Point(239, 854);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(559, 15);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Matrix text には、次の情報を記載 : f cx cy r11 r12 r13 r21 r22 r23 r31 r32 r33 t1 t2 t3";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(904, 899);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->m_button2);
			this->Controls->Add(this->m_button1);
			this->Controls->Add(this->m_panel);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void m_button1_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void m_button2_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void m_panel_Resize (System::Object^ sender, System::EventArgs^ e);
	private: System::Void m_panel_Paint  (System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	private: System::Void m_panel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void m_panel_MouseUp  (System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void m_panel_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
};
}
