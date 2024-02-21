//
// Created by 35691 on 2/21/2024.
//

#include "FileDialog.h"

#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32)

#include <windows.h>
#include <shobjidl.h>
#include <iostream>

bool FileDialog::init() {

    // Create the FileOpenDialog object.
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL,
                                  IID_IFileOpenDialog, reinterpret_cast<void **>(&this->pFileOpenDialog));
    return SUCCEEDED(hr);
}

bool FileDialog::show() {
    // Show the Open dialog box.
    HRESULT hr = this->pFileOpenDialog->Show(nullptr);

    return SUCCEEDED(hr);
}

std::vector<std::string> &FileDialog::getSelectedResult() {
    IShellItem *pItem = nullptr;
    std::string result;
    PWSTR pszFilePath = nullptr;

    do {
        HRESULT hr = this->pFileOpenDialog->GetResult(&pItem);
        if (!SUCCEEDED(hr)) {
            break;
        }
        hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
        if (!SUCCEEDED(hr)) {
            break;
        }

        int len = WideCharToMultiByte(CP_ACP, 0, pszFilePath, wcslen(pszFilePath), nullptr, 0, nullptr, nullptr);
        if (len <= 0) {
            break;
        }
        char *buffer = new char[len + 1];
        if (buffer == nullptr) {
            std::cout << "Error New Buffer" << std::endl;
            break;
        }
        WideCharToMultiByte(CP_ACP, 0, pszFilePath, wcslen(pszFilePath), buffer, len + 1, nullptr, nullptr);

        buffer[len] = '\0';
        result.append(buffer);
        delete[] buffer;
    } while (false);

    if (!result.empty()) {
        this->selectedList.emplace_back(result);
    }
    if (pszFilePath != nullptr) {
        CoTaskMemFree(pszFilePath);
    }
    if (pszFilePath != nullptr) {
        pItem->Release();
    }

    return this->selectedList;
}

FileDialog &FileDialog::clear() {
    selectedList.clear();
    if (pFileOpenDialog != nullptr) {
        pFileOpenDialog->Release();
    }
    pFileOpenDialog = nullptr;
    return *this;
}

#endif
