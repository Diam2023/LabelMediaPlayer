//
// Created by 35691 on 2/21/2024.
//
#pragma once

#include <string>
#include <vector>
#include "axmol.h"


#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32)

#include <windows.h>
#include <shobjidl.h>

#endif

class FileDialog {

private:

#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32)
    IFileOpenDialog *pFileOpenDialog = nullptr;
#endif

protected:

    /**
     * The Selected Files
     */
    std::vector<std::string> selectedList;

public:

    bool init();

    /**
     * Show File Dialog
     * @return Instance For Chain Call
     */
    bool show();

    /**
     * Wait Future Support
     * @return thisInstance
     */
    FileDialog &setFilter();

    FileDialog &multiSelect();

    std::vector<std::string> &getSelectedResult();

    FileDialog &clear();

    /**
     * @return Instance
     */
    static FileDialog &getInstance() {
        static FileDialog fileDialog;
        return fileDialog;
    }

};

