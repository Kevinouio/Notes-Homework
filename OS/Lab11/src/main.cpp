#include <algorithm>
#include <iostream>

#include "cse4733/FileSystem.hpp"
#include "cse4733/FileAlreadyExistsException.hpp"
#include "cse4733/FileMissingException.hpp"
#include "cse4733/NoAvailableInodeException.hpp"
#include "cse4733/NoFreeBlockAvailableException.hpp"
#include "cse4733/UnformattedFilesystemException.hpp"

void stepFormat(cse4733::FileSystem &fs)
{
    std::cout << "Step 1: Formatting the filesystem\n";
    try
    {
        fs.format();
    }
    catch (const cse4733::UnformattedFilesystemException &e)
    {
        std::cerr << "Error: Filesystem could not be formatted.\n";
        return;
    }

    // Check that the file list is empty
    try
    {
        std::vector<std::string> files = fs.listFiles();
        if (files.empty())
        {
            std::cout << "   Filesystem format check: PASS - No files found after format\n";
        }
        else
        {
            std::cout << "   Filesystem format check: FAIL - Files found after format\n";
        }
    }
    catch (const cse4733::UnformattedFilesystemException &e)
    {
        std::cerr << "Error: Filesystem is not formatted.\n";
        return;
    }

    // Attempt to read a file that shouldn't exist
    try
    {
        std::string data = fs.readFile("nonexistent.txt");
        if (data.empty())
        {
            std::cout << "   Filesystem format check: PASS - Reading non-existent file returned empty\n";
        }
        else
        {
            std::cout << "   Filesystem format check: FAIL - Non-existent file returned unexpected data\n";
        }
    }
    catch (const cse4733::UnformattedFilesystemException &e)
    {
        std::cerr << "Error: Filesystem is not formatted.\n";
        return;
    }

    // Check that all blocks are free (optional, if such a function exists)
    try
    {
        size_t freeBlocks = fs.getFreeBlockCount();   // Assuming getFreeBlockCount is implemented
        size_t totalBlocks = fs.getTotalBlockCount(); // Assuming getTotalBlockCount is implemented
        if (freeBlocks == totalBlocks)
        {
            std::cout << "   Filesystem format check: PASS - All blocks are free after format\n";
        }
        else
        {
            std::cout << "   Filesystem format check: FAIL - Unexpected block allocation after format\n";
        }
    }
    catch (const cse4733::UnformattedFilesystemException &e)
    {
        std::cerr << "Error: Filesystem is not formatted.\n";
        return;
    }
}

void stepCreateFiles(cse4733::FileSystem &fs)
{
    std::cout << "\nStep 2: Creating files\n";

    // List of filenames to create
    std::vector<std::string> filenames = {"file1.txt", "file2.txt", "file3.txt"};

    // Iterate through each filename and attempt to create it
    for (const auto &filename : filenames)
    {
        try
        {
            bool success = fs.createFile(filename);
            if (success)
            {
                std::cout << "   Created " << filename << "\n";
            }
            else
            {
                std::cout << "   Failed to create " << filename << "\n";
            }
        }
        catch (const cse4733::UnformattedFilesystemException &e)
        {
            std::cerr << "Error: Filesystem is not formatted.\n";
            return;
        }
        catch (const cse4733::NoAvailableInodeException &e)
        {
            std::cerr << "Error: No available inode.\n";
            return;
        }
    }

    // Verify that each file exists and is empty
    for (const auto &filename : filenames)
    {
        try
        {
            std::string content = fs.readFile(filename);
            if (content.empty())
            {
                std::cout << "   " << filename << " exists and is empty as expected.\n";
            }
            else
            {
                std::cout << "   " << filename << " exists but is not empty (unexpected content: '" << content << "').\n";
            }
        }
        catch (const cse4733::UnformattedFilesystemException &e)
        {
            std::cerr << "Error: Filesystem is not formatted.\n";
            return;
        }
        catch (const cse4733::FileMissingException &e)
        {
            std::cerr << "Error: File " << filename << " does not exist.\n";
            return;
        }
    }
}

void stepWriteData(cse4733::FileSystem &fs)
{
    std::cout << "\nStep 3: Writing data to files\n";

    // Define filenames and their corresponding data to be written
    std::vector<std::pair<std::string, std::string>> fileData = {
        {"file1.txt", "This is the content of file1."},
        {"file2.txt", "File2 contains a different message."},
        {"file3.txt", "file3.txt stores some unique data."}};

    // Iterate over each file and write the corresponding data
    for (const auto &[filename, data] : fileData)
    {
        try
        {
            bool success = fs.writeFile(filename, data);
            if (success)
            {
                std::cout << "   Written to " << filename << ": \"" << data << "\"\n";
            }
            else
            {
                std::cout << "   Failed to write to " << filename << "\n";
            }
        }
        catch (const cse4733::UnformattedFilesystemException &e)
        {
            std::cerr << "Error: Filesystem is not formatted.\n";
            return;
        }
        catch (const cse4733::FileMissingException &e)
        {
            std::cerr << "Error: File " << filename << " does not exist.\n";
            return;
        }
        catch (const cse4733::NoFreeBlockAvailableException &e)
        {
            std::cerr << "Error: No free blocks available.\n";
            return;
        }
    }

    // Verify that each file contains the expected data
    for (const auto &[filename, expectedData] : fileData)
    {
        try
        {
            std::string actualData = fs.readFile(filename);
            if (actualData == expectedData)
            {
                std::cout << "   " << filename << " contains the correct data.\n";
            }
            else
            {
                std::cout << "   " << filename << " contains incorrect data (expected: \"" << expectedData << "\", got: \"" << actualData << "\").\n";
            }
        }
        catch (const cse4733::UnformattedFilesystemException &e)
        {
            std::cerr << "Error: Filesystem is not formatted.\n";
            return;
        }
        catch (const cse4733::FileMissingException &e)
        {
            std::cerr << "Error: File " << filename << " does not exist.\n";
            return;
        }
    }
}

void stepReadData(cse4733::FileSystem &fs)
{
    std::cout << "\nStep 4: Reading data from files and verifying content\n";

    // Define filenames and their corresponding expected data (from Step 2)
    std::vector<std::pair<std::string, std::string>> fileData = {
        {"file1.txt", "This is the content of file1."},
        {"file2.txt", "File2 contains a different message."},
        {"file3.txt", "file3.txt stores some unique data."}};

    // Iterate over each file and read its content
    for (const auto &[filename, expectedData] : fileData)
    {
        try
        {
            std::string actualData = fs.readFile(filename);

            // Verify that the content matches the expected data
            if (actualData == expectedData)
            {
                std::cout << "   " << filename << " contains the correct data: \"" << actualData << "\"\n";
            }
            else
            {
                std::cout << "   " << filename << " contains incorrect data (expected: \""
                          << expectedData << "\", got: \"" << actualData << "\").\n";
            }
        }
        catch (const cse4733::UnformattedFilesystemException &e)
        {
            std::cerr << "Error: Filesystem is not formatted.\n";
            return;
        }
        catch (const cse4733::FileMissingException &e)
        {
            std::cerr << "Error: File " << filename << " does not exist.\n";
            return;
        }
    }
}

void stepDeleteFiles(cse4733::FileSystem &fs)
{
    std::cout << "\nStep 5: Deleting files and verifying their absence\n";

    // List of filenames to delete
    std::vector<std::string> filenames = {"file1.txt", "file2.txt", "file3.txt"};

    // Delete each file and confirm deletion
    for (const auto &filename : filenames)
    {
        try
        {
            bool success = fs.deleteFile(filename);
            if (success)
            {
                std::cout << "   Deleted " << filename << "\n";
            }
            else
            {
                std::cout << "   Failed to delete " << filename << "\n";
            }
        }
        catch (const cse4733::UnformattedFilesystemException &e)
        {
            std::cerr << "Error: Filesystem is not formatted.\n";
            return;
        }
        catch (const cse4733::FileMissingException &e)
        {
            std::cerr << "Error: File " << filename << " does not exist.\n";
            return;
        }
    }

    // Verify that each file is absent by attempting to read and confirming an empty result
    for (const auto &filename : filenames)
    {
        try
        {
            std::string content = fs.readFile(filename);
            if (content.empty())
            {
                std::cout << "   " << filename << " is confirmed absent (read returned empty).\n";
            }
            else
            {
                std::cout << "   " << filename << " still exists unexpectedly (read returned: \"" << content << "\").\n";
            }
        }
        catch (const cse4733::UnformattedFilesystemException &e)
        {
            std::cerr << "Error: Filesystem is not formatted.\n";
            return;
        }
        catch (const cse4733::FileMissingException &e)
        {
            std::cerr << "Error: File " << filename << " does not exist.\n";
            return;
        }
    }

    // Verify that deleted files do not appear in the file listing
    try
    {
        std::vector<std::string> files = fs.listFiles();
        for (const auto &filename : filenames)
        {
            if (std::find(files.begin(), files.end(), filename) == files.end())
            {
                std::cout << "   " << filename << " is not listed (expected).\n";
            }
            else
            {
                std::cout << "   " << filename << " is still listed (unexpected).\n";
            }
        }
    }
    catch (const cse4733::UnformattedFilesystemException &e)
    {
        std::cerr << "Error: Filesystem is not formatted.\n";
        return;
    }
}

void repeatStepFormat(cse4733::FileSystem &fs)
{
    std::cout << "\nRepeating Step 1: Formatting the filesystem again to reset state\n";

    try
    {
        // Format the filesystem
        fs.format();
    }
    catch (const cse4733::UnformattedFilesystemException &e)
    {
        std::cerr << "Error: Filesystem could not be formatted.\n";
        return;
    }

    // Verify that the file list is empty after formatting
    try
    {
        std::vector<std::string> files = fs.listFiles();
        if (files.empty())
        {
            std::cout << "   Filesystem format check: PASS - No files found after format\n";
        }
        else
        {
            std::cout << "   Filesystem format check: FAIL - Files found after format\n";
        }
    }
    catch (const cse4733::UnformattedFilesystemException &e)
    {
        std::cerr << "Error: Filesystem is not formatted.\n";
        return;
    }

    // Attempt to read a non-existent file to confirm it's empty
    try
    {
        std::string filename = "nonexistent.txt";
        std::string content = fs.readFile(filename);
        if (content.empty())
        {
            std::cout << "   Filesystem format check: PASS - Reading non-existent file returned empty\n";
        }
        else
        {
            std::cout << "   Filesystem format check: FAIL - Non-existent file returned unexpected data\n";
        }
    }
    catch (const cse4733::UnformattedFilesystemException &e)
    {
        std::cerr << "Error: Filesystem is not formatted.\n";
        return;
    }
}

void stepTestBeforeFormat(cse4733::FileSystem &fs)
{
    std::cout << "\nStep 7: Testing that operations cannot run before formatting\n";

    // Attempt to create a file without formatting
    try
    {
        bool createResult = fs.createFile("unformattedFile.txt");
        std::cout << "   Operation check: FAIL - File creation succeeded unexpectedly before formatting\n";
    }
    catch (const cse4733::UnformattedFilesystemException &e)
    {
        std::cout << "   Operation check: PASS - File creation threw UnformattedFilesystemException as expected\n";
    }

    // Attempt to read a file without formatting
    try
    {
        std::string readResult = fs.readFile("unformattedFile.txt");
        std::cout << "   Operation check: FAIL - File read returned data unexpectedly before formatting\n";
    }
    catch (const cse4733::UnformattedFilesystemException &e)
    {
        std::cout << "   Operation check: PASS - File read threw UnformattedFilesystemException as expected\n";
    }

    // Attempt to write data to a file without formatting
    try
    {
        bool writeResult = fs.writeFile("unformattedFile.txt", "This should not be written.");
        std::cout << "   Operation check: FAIL - File write succeeded unexpectedly before formatting\n";
    }
    catch (const cse4733::UnformattedFilesystemException &e)
    {
        std::cout << "   Operation check: PASS - File write threw UnformattedFilesystemException as expected\n";
    }

    // Attempt to list files without formatting
    try
    {
        std::vector<std::string> files = fs.listFiles();
        std::cout << "   Operation check: FAIL - File list is not empty unexpectedly before formatting\n";
    }
    catch (const cse4733::UnformattedFilesystemException &e)
    {
        std::cout << "   Operation check: PASS - File list threw UnformattedFilesystemException as expected\n";
    }
}

int main()
{
    // Create a filesystem with 1000 blocks of 64 bytes each
    cse4733::FileSystem fs(1000 * 64, 64);

    stepFormat(fs);
    stepCreateFiles(fs);
    stepWriteData(fs);
    stepReadData(fs);
    stepDeleteFiles(fs);
    repeatStepFormat(fs);

    cse4733::FileSystem fs2(1000 * 64, 64);
    stepTestBeforeFormat(fs2);

    return 0;
}
