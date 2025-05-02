#pragma once

using namespace System;
using namespace System::Diagnostics;
using namespace System::Security::Principal;
using namespace System::Windows::Forms;

inline bool IsAdministrator() {
    WindowsIdentity^ identity = WindowsIdentity::GetCurrent();
    WindowsPrincipal^ principal = gcnew WindowsPrincipal(identity);
    return principal->IsInRole(WindowsBuiltInRole::Administrator);
}

inline void RestartAsAdmin() {
    ProcessStartInfo^ startInfo = gcnew ProcessStartInfo();
    startInfo->FileName = Application::ExecutablePath;
    startInfo->Verb = "runas";
    Process::Start(startInfo);
    Application::Exit();
}
#pragma once
