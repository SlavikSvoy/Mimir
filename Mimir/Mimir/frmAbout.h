#pragma once

namespace Mimir {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;

	public ref class frmAbout : public Form {
	public:
		frmAbout() {
			InitializeComponent();
		}

	private:
		void InitializeComponent() {
			this->Text = "Про застосунок";
			this->Size = Drawing::Size(450, 320);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->BackColor = Color::White;


			// Логотип
			PictureBox^ pbIcon = gcnew PictureBox();
			pbIcon->Location = Point(20, 20);
			pbIcon->Size = Drawing::Size(64, 64);
			pbIcon->BackColor = Color::LightSkyBlue;
			pbIcon->BorderStyle = BorderStyle::FixedSingle;
			// pbIcon->Image = Image::FromFile("logo.png"); // якщо є зображення

			// Назва застосунку
			Label^ lblName = gcnew Label();
			lblName->Text = "Mimir – Менеджер режиму відновлення";
			lblName->Location = Point(100, 25);
			lblName->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
			lblName->ForeColor = Color::SteelBlue;
			lblName->AutoSize = true;

			// Версія
			Label^ lblVersion = gcnew Label();
			lblVersion->Text = "Версія: 1.0.0";
			lblVersion->Location = Point(100, 55);
			lblVersion->Font = gcnew Drawing::Font("Segoe UI", 9);
			lblVersion->AutoSize = true;

			// Автор
			Label^ lblAuthor = gcnew Label();
			lblAuthor->Text = "Автор: Зелінський В.В 6пі-22б";
			lblAuthor->Location = Point(100, 80);
			lblAuthor->Font = gcnew Drawing::Font("Segoe UI", 9);
			lblAuthor->AutoSize = true;

			// Права
			Label^ lblRights = gcnew Label();
			lblRights->Text = "© 2025 Усі права захищені";
			lblRights->Location = Point(100, 105);
			lblRights->Font = gcnew Drawing::Font("Segoe UI", 9, FontStyle::Italic);
			lblRights->AutoSize = true;

			// Інформація
			Label^ lblInfo = gcnew Label();
			lblInfo->Text = "Застосунок дозволяє керувати режимом відновлення ОС.";
			lblInfo->Location = Point(20, 150);
			lblInfo->Font = gcnew Drawing::Font("Segoe UI", 9);
			lblInfo->Size = Drawing::Size(400, 40);
			lblInfo->ForeColor = Color::DimGray;

			// Кнопка закриття
			Button^ btnClose = gcnew Button();
			btnClose->Text = "Закрити";
			btnClose->Size = Drawing::Size(80, 30);
			btnClose->Location = Point((this->ClientSize.Width - btnClose->Width) / 2, 220);
			btnClose->BackColor = Color::LightSkyBlue;
			btnClose->FlatStyle = FlatStyle::Flat;
			btnClose->Click += gcnew EventHandler(this, &frmAbout::CloseAbout);

			// Додати всі елементи
			this->Controls->Add(pbIcon);
			this->Controls->Add(lblName);
			this->Controls->Add(lblVersion);
			this->Controls->Add(lblAuthor);
			this->Controls->Add(lblRights);
			this->Controls->Add(lblInfo);
			this->Controls->Add(btnClose);
		}

		void CloseAbout(Object^ sender, EventArgs^ e) {
			this->Close();
		}
	};
}
