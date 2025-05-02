#include "frmMain.h"
#include "AdminUtils.h"  

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args) {
    try {
        // Перевірка прав
        if (!IsAdministrator()) {
            RestartAsAdmin();
            return 0;
        }

        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false);
        Mimir::frmMain form;
        Application::Run(%form);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Помилка: " + ex->Message, "Помилка програми",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
    return 0;
}
