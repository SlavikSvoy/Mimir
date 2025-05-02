#pragma once
#include "frmAbout.h"
#include "AdminUtils.h"

namespace Mimir {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::IO;
    using namespace System::Diagnostics;

    public ref class frmMain : public Form {
    public:
        frmMain() {
            InitializeComponent();
            InitTreeView();
        }

    protected:
        ~frmMain() {}

    private:
        MenuStrip^ mnsMain;
        ToolStrip^ tsQuickAccess;
        ToolStripMenuItem^ tsmiFile;
        ToolStripMenuItem^ tsmiProcess;
        ToolStripMenuItem^ tsmiInfo;

        TreeView^ tvMain;
        ListView^ lvMain;
        Panel^ pnlInfo;
        TextBox^ txbInfo;
        TabControl^ tabControl;

        StatusStrip^ scMain;
        ToolStripStatusLabel^ tslInfo;
        ToolStripProgressBar^ tspMain;

        Button^ btnEnableRE;
        Button^ btnDisableRE;
        Button^ btnCheckStatus;
        Button^ btnRebootToRE;

        void InitializeComponent(void) {
            this->Text = "Mimir – Менеджер режиму відновлення ОС";
            this->Size = Drawing::Size(1000, 600);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::LightSteelBlue;

            // Меню
            mnsMain = gcnew MenuStrip();
            tsmiFile = gcnew ToolStripMenuItem("Файл");
            tsmiProcess = gcnew ToolStripMenuItem("Процес");
            tsmiInfo = gcnew ToolStripMenuItem("Інформація");

            tsmiFile->DropDownItems->AddRange(gcnew array<ToolStripItem^> {
                gcnew ToolStripMenuItem("Новий", nullptr, gcnew EventHandler(this, &frmMain::NewFile)),
                    gcnew ToolStripMenuItem("Відкрити", nullptr, gcnew EventHandler(this, &frmMain::OpenFile)),
                    gcnew ToolStripMenuItem("Зберегти", nullptr, gcnew EventHandler(this, &frmMain::SaveFile)),
                    gcnew ToolStripMenuItem("Вихід", nullptr, gcnew EventHandler(this, &frmMain::ExitApplication))
            });
            tsmiProcess->DropDownItems->AddRange(gcnew array<ToolStripItem^> {
                gcnew ToolStripMenuItem("Виконати", nullptr, gcnew EventHandler(this, &frmMain::btnEnableRE_Click)),
                    gcnew ToolStripMenuItem("Відміна", nullptr, gcnew EventHandler(this, &frmMain::btnDisableRE_Click))
            });
            tsmiInfo->DropDownItems->Add(gcnew ToolStripMenuItem("Про програму", nullptr, gcnew EventHandler(this, &frmMain::ShowAbout)));

            mnsMain->Items->AddRange(gcnew array<ToolStripItem^>{ tsmiFile, tsmiProcess, tsmiInfo });
            mnsMain->Dock = DockStyle::Top;
            this->MainMenuStrip = mnsMain;
            this->Controls->Add(mnsMain);

            // Панель швидкого доступу
            tsQuickAccess = gcnew ToolStrip();
            tsQuickAccess->Dock = DockStyle::Top;
            tsQuickAccess->Items->AddRange(gcnew array<ToolStripItem^> {
                gcnew ToolStripButton("Новий", nullptr, gcnew EventHandler(this, &frmMain::NewFile)),
                    gcnew ToolStripButton("Відкрити", nullptr, gcnew EventHandler(this, &frmMain::OpenFile)),
                    gcnew ToolStripButton("Зберегти", nullptr, gcnew EventHandler(this, &frmMain::SaveFile)),
                    gcnew ToolStripButton("Виконати", nullptr, gcnew EventHandler(this, &frmMain::btnEnableRE_Click)),
                    gcnew ToolStripButton("Відміна", nullptr, gcnew EventHandler(this, &frmMain::btnDisableRE_Click)),
                    gcnew ToolStripButton("Про програму", nullptr, gcnew EventHandler(this, &frmMain::ShowAbout))
            });
            this->Controls->Add(tsQuickAccess);

            // TreeView
            tvMain = gcnew TreeView();
            tvMain->Location = Point(10, 80);
            tvMain->Size = Drawing::Size(200, 400);
            tvMain->AfterSelect += gcnew TreeViewEventHandler(this, &frmMain::tvMain_AfterSelect);
            this->Controls->Add(tvMain);

            // ListView
            lvMain = gcnew ListView();
            lvMain->Location = Point(220, 80);
            lvMain->Size = Drawing::Size(350, 400);
            lvMain->View = View::Details;
            lvMain->Columns->Add("Назва", 150);
            lvMain->Columns->Add("Тип", 100);
            lvMain->Columns->Add("Розмір", 80);
            this->Controls->Add(lvMain);

            // Панель інформації
            pnlInfo = gcnew Panel();
            pnlInfo->Location = Point(580, 80);
            pnlInfo->Size = Drawing::Size(390, 120);
            pnlInfo->BackColor = Color::LightSlateGray;
            txbInfo = gcnew TextBox();
            txbInfo->Multiline = true;
            txbInfo->ScrollBars = ScrollBars::Vertical;
            txbInfo->Dock = DockStyle::Fill;
            pnlInfo->Controls->Add(txbInfo);
            this->Controls->Add(pnlInfo);

            // Кнопки
            btnCheckStatus = gcnew Button();
            btnCheckStatus->Text = "Перевірити статус";
            btnCheckStatus->Location = Point(600, 220);
            btnCheckStatus->Click += gcnew EventHandler(this, &frmMain::btnCheckStatus_Click);

            btnEnableRE = gcnew Button();
            btnEnableRE->Text = "Увімкнути RE";
            btnEnableRE->Location = Point(600, 260);
            btnEnableRE->Click += gcnew EventHandler(this, &frmMain::btnEnableRE_Click);

            btnDisableRE = gcnew Button();
            btnDisableRE->Text = "Вимкнути RE";
            btnDisableRE->Location = Point(600, 300);
            btnDisableRE->Click += gcnew EventHandler(this, &frmMain::btnDisableRE_Click);

            btnRebootToRE = gcnew Button();
            btnRebootToRE->Text = "REBOOT";
            btnRebootToRE->BackColor = Color::Red;
            btnRebootToRE->Location = Point(600, 340);
            btnRebootToRE->Size = Drawing::Size(120, 40);
            btnRebootToRE->Click += gcnew EventHandler(this, &frmMain::btnRebootToRE_Click);

            this->Controls->Add(btnCheckStatus);
            this->Controls->Add(btnEnableRE);
            this->Controls->Add(btnDisableRE);
            this->Controls->Add(btnRebootToRE);

            // Статус бар
            scMain = gcnew StatusStrip();
            tslInfo = gcnew ToolStripStatusLabel("Готово");
            tspMain = gcnew ToolStripProgressBar();
            tspMain->Size = Drawing::Size(150, 16);
            scMain->Items->Add(tslInfo);
            scMain->Items->Add(tspMain);
            this->Controls->Add(scMain);
        }

        void InitTreeView() {
            tvMain->Nodes->Clear();
            for each (String ^ drive in Directory::GetLogicalDrives()) {
                TreeNode^ root = gcnew TreeNode(drive);
                root->Nodes->Add(gcnew TreeNode("..."));
                tvMain->Nodes->Add(root);
            }
            tvMain->BeforeExpand += gcnew TreeViewCancelEventHandler(this, &frmMain::tvMain_BeforeExpand);
        }

        void tvMain_BeforeExpand(Object^ sender, TreeViewCancelEventArgs^ e) {
            TreeNode^ node = e->Node;
            if (node->Nodes->Count == 1 && node->Nodes[0]->Text == "...") {
                node->Nodes->Clear();
                try {
                    for each (String ^ dir in Directory::GetDirectories(node->FullPath)) {
                        TreeNode^ sub = gcnew TreeNode(Path::GetFileName(dir));
                        sub->Nodes->Add(gcnew TreeNode("..."));
                        node->Nodes->Add(sub);
                    }
                }
                catch (...) {}
            }
        }

        void tvMain_AfterSelect(Object^ sender, TreeViewEventArgs^ e) {
            lvMain->Items->Clear();
            try {
                for each (String ^ dir in Directory::GetDirectories(e->Node->FullPath)) {
                    ListViewItem^ item = gcnew ListViewItem(Path::GetFileName(dir));
                    item->SubItems->Add("Папка");
                    item->SubItems->Add("");
                    lvMain->Items->Add(item);
                }
                for each (String ^ file in Directory::GetFiles(e->Node->FullPath)) {
                    FileInfo^ fi = gcnew FileInfo(file);
                    ListViewItem^ item = gcnew ListViewItem(fi->Name);
                    item->SubItems->Add("Файл");
                    item->SubItems->Add(fi->Length.ToString());
                    lvMain->Items->Add(item);
                }
            }
            catch (...) {}
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
