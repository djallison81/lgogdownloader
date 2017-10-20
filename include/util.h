/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */

#ifndef UTIL_H
#define UTIL_H

#include "globalconstants.h"
#include "config.h"
#include "globals.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <sstream>
#include <memory>
#include <rhash.h>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <json/json.h>

struct gameItem
{
    std::string name;
    std::string id;
    std::vector<std::string> dlcnames;
    Json::Value gamedetailsjson;
    int updates = 0;
};

struct wishlistItem
{
    std::string title;
    unsigned int platform;
    std::vector<std::string> tags;
    time_t release_date_time;
    std::string currency;
    std::string price;
    std::string discount_percent;
    std::string discount;
    std::string store_credit;
    std::string url;
    bool bIsBonusStoreCreditIncluded;
    bool bIsDiscounted;
};

namespace Util
{
    std::string makeFilepath(const std::string& directory, const std::string& path, const std::string& gamename, std::string subdirectory = "", const unsigned int& platformId = 0, const std::string& dlcname = "", const std::string& gametitle = "", const std::string& dlctitle = "");
    std::string makeRelativeFilepath(const std::string& path, const std::string& gamename, std::string subdirectory = "");
    std::string getFileHash(const std::string& filename, unsigned hash_id);
    std::string getChunkHash(unsigned char* chunk, uintmax_t chunk_size, unsigned hash_id);
    int createXML(std::string filepath, uintmax_t chunk_size, std::string xml_dir = std::string());
    int getGameSpecificConfig(std::string gamename, gameSpecificConfig* conf, std::string directory = std::string());
    int replaceString(std::string& str, const std::string& to_replace, const std::string& replace_with);
    void filepathReplaceReservedStrings(std::string& str, const std::string& gamename, const unsigned int& platformId = 0, const std::string& dlcname = "", const std::string& gametitle = "", const std::string& dlctitle = "");
    void setFilePermissions(const boost::filesystem::path& path, const boost::filesystem::perms& permissions);
    int getTerminalWidth();
    void getDownloaderUrlsFromJSON(const Json::Value &root, std::vector<std::string> &urls);
    std::vector<std::string> getDLCNamesFromJSON(const Json::Value &root);
    std::string getHomeDir();
    std::string getConfigHome();
    std::string getCacheHome();
    std::vector<std::string> tokenize(const std::string& str, const std::string& separator = ",");
    unsigned int getOptionValue(const std::string& str, const std::vector<GlobalConstants::optionsStruct>& options, const bool& bAllowStringToIntConversion = true);
    std::string getOptionNameString(const unsigned int& value, const std::vector<GlobalConstants::optionsStruct>& options);
    void parseOptionString(const std::string &option_string, std::vector<unsigned int> &priority, unsigned int &type, const std::vector<GlobalConstants::optionsStruct>& options);
    std::string getLocalFileHash(const std::string& xml_dir, const std::string& filepath, const std::string& gamename = std::string());
    void shortenStringToTerminalWidth(std::string& str);
    std::string getJsonUIntValueAsString(const Json::Value& json);

    template<typename ... Args> std::string formattedString(const std::string& format, Args ... args)
    {
        std::size_t sz = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // +1 for null terminator
        std::unique_ptr<char[]> buf(new char[sz]);
        std::snprintf(buf.get(), sz, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + sz - 1); // -1 because we don't want the null terminator
    }
}

#endif // UTIL_H
