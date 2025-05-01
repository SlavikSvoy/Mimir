#include "frmMain.h"
#include <Windows.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Security::Principal;  // Додано для WindowsIdentity та WindowsPrincipal
using namespace System::Diagnostics;          // Додано для ProcessStartInfo та Process

// Перевірка чи програма працює з правами адміністратора
bool IsAdministrator() {
    WindowsIdentity^ identity = WindowsIdentity::GetCurrent();
    WindowsPrincipal^ principal = gcnew WindowsPrincipal(identity);
    return principal->IsInRole(WindowsBuiltInRole::Administrator);
}

// Перезапуск програми з правами адміністратора
void RestartAsAdmin() {
    ProcessStartInfo^ startInfo = gcnew ProcessStartInfo();
    startInfo->FileName = Application::ExecutablePath;
    startInfo->Verb = "runas"; // Запуск з правами адміністратора
    Process::Start(startInfo);
    Application::Exit(); // Закриваємо поточний процес
}

[STAThread]
int main(array<String^>^ args) {
    try {
        // Перевірка на права адміністратора
        if (!IsAdministrator()) {
            RestartAsAdmin(); // Перезапускаємо програму з правами адміністратора
            return 0; // Завершуємо поточний запуск
            if (!IsAdministrator()) {
                MessageBox::Show("Ця програма потребує прав адміністратора для роботи.",
                    "Попередження", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                RestartAsAdmin();
                return 0;
            }
        }

        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false);
        Mimir::frmMain form;
        Application::Run(% form);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Помилка: " + ex->Message, "Помилка програми", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
    return 0;
}
