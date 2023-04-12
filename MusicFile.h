#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <iterator>

#include "thirdparty/aes.h"
#include "thirdparty/cJSON.h"

class MusicFile
{
public:
	MusicFile(const std::string& fileName);

	void readFileData();

	void saveDecryptedMusic();

private:
	std::string fileName_;
	std::vector<unsigned char> rc4Key_;
	std::vector<unsigned char> meta_;
	std::vector<unsigned char> img_;
	std::vector<unsigned char> musicData_;
};

