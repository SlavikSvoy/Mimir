#pragma once
#include "frmAbout.h"
#include "AdminUtils.h"


namespace Mimir {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Diagnostics;
	using namespace System::IO;
	using namespace System::Security::Principal;



	


	public ref class frmMain : public Form {
	public:
		frmMain() {
			InitializeComponent();
		}

	protected:
		~frmMain() {}

	private:
		MenuStrip^ mnsMain;
		ToolStripMenuItem^ tsmiFile;
		ToolStripMenuItem^ tsmiProcess;
		ToolStripMenuItem^ tsmiInfo;
		ToolStripMenuItem^ tsmiExit;
		ToolStripMenuItem^ tsmiStartProcess;
		ToolStripMenuItem^ tsmiCancelProcess;

		ToolStrip^ tsMain;
		ToolStripButton^ tsbNew;
		ToolStripButton^ tsbOpen;
		ToolStripButton^ tsbSave;
		ToolStripButton^ tsbExecute;
		ToolStripButton^ tsbCancel;
		ToolStripButton^ tsbAbout;

		TreeView^ tvMain;
		ListView^ lvMain;

		Panel^ pnlInfo;
		Label^ lblInfo;
		TextBox^ txbInfo;

		StatusStrip^ scMain;
		ToolStripStatusLabel^ tslInfo;
		ToolStripProgressBar^ tspMain;

		Button^ btnCheckStatus;
		Button^ btnEnableRE;
		Button^ btnDisableRE;
		Button^ btnRebootToRE;

		void InitializeComponent(void) {
			this->Text = "Mimir – Менеджер режиму відновлення ОС";
			this->Size = Drawing::Size(900, 600);
			this->StartPosition = FormStartPosition::CenterScreen;
			this->BackColor = Color::LightSkyBlue;
			this->Icon = gcnew System::Drawing::Icon("logo.ico");

			mnsMain = gcnew MenuStrip();
			tsmiFile = gcnew ToolStripMenuItem("Файл");
			tsmiProcess = gcnew ToolStripMenuItem("Процес");
			tsmiInfo = gcnew ToolStripMenuItem("Інформація");
			tsmiExit = gcnew ToolStripMenuItem("Вихід");
			tsmiStartProcess = gcnew ToolStripMenuItem("Виконати");
			tsmiCancelProcess = gcnew ToolStripMenuItem("Скасувати");

			ToolStripMenuItem^ tsmiAbout = gcnew ToolStripMenuItem("Про застосунок");
			tsmiAbout->Click += gcnew EventHandler(this, &frmMain::ShowAbout);

			tsmiFile->DropDownItems->Add(tsmiExit);
			tsmiProcess->DropDownItems->Add(tsmiStartProcess);
			tsmiProcess->DropDownItems->Add(tsmiCancelProcess);
			tsmiInfo->DropDownItems->Add(tsmiAbout);

			tsmiExit->Click += gcnew EventHandler(this, &frmMain::ExitApplication);
			tsmiStartProcess->Click += gcnew EventHandler(this, &frmMain::btnEnableRE_Click);
			tsmiCancelProcess->Click += gcnew EventHandler(this, &frmMain::btnDisableRE_Click);

			mnsMain->Items->AddRange(gcnew array<ToolStripItem^>{ tsmiFile, tsmiProcess, tsmiInfo });
			this->MainMenuStrip = mnsMain;
			this->Controls->Add(mnsMain);

			tsMain = gcnew ToolStrip();
			tsbNew = gcnew ToolStripButton("New");
			tsbOpen = gcnew ToolStripButton("Open");
			tsbSave = gcnew ToolStripButton("Save");
			tsbExecute = gcnew ToolStripButton("Execute");
			tsbCancel = gcnew ToolStripButton("Cancel");
			tsbAbout = gcnew ToolStripButton("About");
			tsbAbout->Click += gcnew EventHandler(this, &frmMain::ShowAbout);

			tsbNew->Click += gcnew EventHandler(this, &frmMain::NewFile);
			tsbOpen->Click += gcnew EventHandler(this, &frmMain::OpenFile);
			tsbSave->Click += gcnew EventHandler(this, &frmMain::SaveFile);
			tsbExecute->Click += gcnew EventHandler(this, &frmMain::btnEnableRE_Click);
			tsbCancel->Click += gcnew EventHandler(this, &frmMain::btnDisableRE_Click);

			tsMain->Items->AddRange(gcnew array<ToolStripItem^>{
				tsbNew, tsbOpen, tsbSave, tsbExecute, tsbCancel, tsbAbout
			});
			tsMain->Location = Point(0, 24);
			this->Controls->Add(tsMain);

			tvMain = gcnew TreeView();
			tvMain->Location = Point(10, 60);
			tvMain->Size = Drawing::Size(200, 400);
			this->Controls->Add(tvMain);

			lvMain = gcnew ListView();
			lvMain->Location = Point(220, 60);
			lvMain->Size = Drawing::Size(300, 400);
			this->Controls->Add(lvMain);

			btnCheckStatus = gcnew Button();
			btnCheckStatus->Text = "Перевірити статус";
			btnCheckStatus->Location = Point(550, 200);
			btnCheckStatus->Click += gcnew EventHandler(this, &frmMain::btnCheckStatus_Click);

			btnEnableRE = gcnew Button();
			btnEnableRE->Text = "Увімкнути RE";
			btnEnableRE->Location = Point(550, 240);
			btnEnableRE->Click += gcnew EventHandler(this, &frmMain::btnEnableRE_Click);

			btnDisableRE = gcnew Button();
			btnDisableRE->Text = "Вимкнути RE";
			btnDisableRE->Location = Point(550, 280);
			btnDisableRE->Click += gcnew EventHandler(this, &frmMain::btnDisableRE_Click);

			btnRebootToRE = gcnew Button();
			btnRebootToRE->Text = "REBOOT";
			btnRebootToRE->Location = Point(550, 320);
			btnRebootToRE->Size = Drawing::Size(120, 40); // Збільшений розмір кнопки
			btnRebootToRE->BackColor = Color::Red; // Червоний колір фону
			btnRebootToRE->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold); // Збільшений і жирний шрифт
			btnRebootToRE->Click += gcnew EventHandler(this, &frmMain::btnRebootToRE_Click);

			ToolTip^ toolTip = gcnew ToolTip();
			toolTip->SetToolTip(btnEnableRE, "Увімкнення середовища відновлення (RE).");
			toolTip->SetToolTip(btnDisableRE, "Вимкнення середовища відновлення (RE).");
			toolTip->SetToolTip(btnCheckStatus, "Перевірка поточного стану середовища відновлення.");
			toolTip->SetToolTip(btnRebootToRE, "Перезавантаження системи в середовище відновлення.");

			this->Controls->Add(btnCheckStatus);
			this->Controls->Add(btnEnableRE);
			this->Controls->Add(btnDisableRE);
			this->Controls->Add(btnRebootToRE);

			pnlInfo = gcnew Panel();
			pnlInfo->Location = Point(530, 60);
			pnlInfo->Size = Drawing::Size(340, 100);
			pnlInfo->BackColor = Color::SteelBlue;

			lblInfo = gcnew Label();
			lblInfo->Text = "Обсяг обробки:";
			lblInfo->ForeColor = Color::White;
			lblInfo->Location = Point(10, 10);
			lblInfo->Size = Drawing::Size(120, 20);

			txbInfo = gcnew TextBox();
			txbInfo->Location = Point(10, 40);
			txbInfo->Size = Drawing::Size(320, 50);
			txbInfo->Multiline = true;
			txbInfo->ScrollBars = ScrollBars::Vertical;

			pnlInfo->Controls->Add(lblInfo);
			pnlInfo->Controls->Add(txbInfo);
			this->Controls->Add(pnlInfo);

			scMain = gcnew StatusStrip();
			tslInfo = gcnew ToolStripStatusLabel("Готово");
			tspMain = gcnew ToolStripProgressBar();
			tspMain->Size = Drawing::Size(150, 16);
			scMain->Items->Add(tslInfo);
			scMain->Items->Add(tspMain);
			scMain->Location = Point(0, this->ClientSize.Height - 22);
			scMain->Anchor = AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right;
			this->Controls->Add(scMain);
		}

		String^ ExecuteCommand(String^ command) {
			ProcessStartInfo^ psi = gcnew ProcessStartInfo("cmd.exe", "/c " + command);
			psi->RedirectStandardOutput = true;
			psi->UseShellExecute = false;
			psi->CreateNoWindow = true;
			Process^ proc = Process::Start(psi);
			String^ output = proc->StandardOutput->ReadToEnd();
			proc->WaitForExit();
			return output;
		}

		void ShowAbout(Object^ sender, EventArgs^ e) {
			frmAbout^ aboutForm = gcnew frmAbout();
			aboutForm->ShowDialog();
		}

		void ExitApplication(Object^ sender, EventArgs^ e) {
			Application::Exit();
		}

		void btnCheckStatus_Click(Object^ sender, EventArgs^ e) {
			tspMain->Visible = true;
			tspMain->Style = ProgressBarStyle::Marquee;
			txbInfo->Text = ExecuteCommand("reagentc /info");
			tspMain->Visible = false;
			tslInfo->Text = "Перевірено статус.";
		}

		void btnEnableRE_Click(Object^ sender, EventArgs^ e) {
			txbInfo->Text = ExecuteCommand("reagentc /enable");
			tslInfo->Text = "RE увімкнено.";
		}


		void btnDisableRE_Click(Object^ sender, EventArgs^ e) {
			txbInfo->Text = ExecuteCommand("reagentc /disable");
			tslInfo->Text = "RE вимкнено.";
		}

		void btnRebootToRE_Click(Object^ sender, EventArgs^ e) {
			ExecuteCommand("shutdown /r /o /f /t 0");
			tslInfo->Text = "reboot";
		}

		void NewFile(Object^ sender, EventArgs^ e) {
			txbInfo->Clear();
			tslInfo->Text = "Новий файл.";
		}

		void OpenFile(Object^ sender, EventArgs^ e) {
			OpenFileDialog^ ofd = gcnew OpenFileDialog();
			ofd->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
			if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				txbInfo->Text = File::ReadAllText(ofd->FileName);
				tslInfo->Text = "Файл відкрито.";
			}
		}

		void SaveFile(Object^ sender, EventArgs^ e) {
			SaveFileDialog^ sfd = gcnew SaveFileDialog();
			sfd->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
			if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				File::WriteAllText(sfd->FileName, txbInfo->Text);
				tslInfo->Text = "Файл збережено.";
			}
		}
	};
}