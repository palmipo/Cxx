#include "log.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#if defined __MINGW32__ ||  defined __CYGWIN__
#include <winsock2.h>
#else
#include <unistd.h>
#endif

Log * Log::_instance = 0;


LogMutex::LogMutex(std::mutex & m)
: m_(m)
{
	m_.lock();
}

LogMutex::~LogMutex()
{
	m_.unlock();
}

Log::Log()
{
	t0 = std::chrono::high_resolution_clock::now();
}

Log * Log::getLogger()
{
	if (!_instance)
	{
		_instance = new Log();
	}

	return _instance;
}

void Log::setFileName(const std::string & fic1, const std::string & fic2)
{
	/*
	char nom_machine[256];
	if (::gethostname(nom_machine, 256))
	{
		error(__FILE__, __LINE__, "lecture impossible du nom de la machine d'execution du programme !");
	}
	std::stringstream ss_file, ss_log, ss_result;
	ss_file << "tturm-" << nom_machine;

	ss_log << ss_file.str() << ".txt";
	filename = ss_log.str();
	
	ss_result << ss_file.str() << "-result.txt";
	filename_result = ss_result.str();
	*/

	filename = fic1;
	filename_result = fic2;
}

void Log::debug(const std::string & fichier, int32_t ligne, const std::string & txt)
{
	libre("DEBUG", fichier, std::to_string(ligne), txt);
}

void Log::info(const std::string & fichier, int32_t ligne, const std::string & txt)
{
	libre("INFO", fichier, std::to_string(ligne), txt);
}

void Log::warn(const std::string & fichier, int32_t ligne, const std::string & txt)
{
	libre("WARNING", fichier, std::to_string(ligne), txt);
}

void Log::error(const std::string & fichier, int32_t ligne, const std::string & txt)
{
	libre("ERROR", fichier, std::to_string(ligne), txt);
}

void Log::fatal(const std::string & fichier, int32_t ligne, const std::string & txt)
{
	libre("FATAL", fichier, std::to_string(ligne), txt);
}

void Log::result(const std::string & fichier, const std::string & ligne, const std::string & OK_KO, const std::string & txt)
{
	std::stringstream ss;
	ss << OK_KO;
	ss << " ";
	ss << txt;

	libre("RESULT", fichier, ligne, ss.str());

	if (!filename_result.empty())
	{
		std::ofstream os_res(filename_result, std::ios::app);
		os_res << ss.str() << std::endl;
	}
}

void Log::libre(const std::string & type, const std::string & fichier, const std::string & ligne, const std::string & txt)
{
	LogMutex mutex(m_);

	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - t0;

	std::stringstream ss;
	ss << std::setfill(' ') << std::setw(10) << std::uppercase << std::string(type, 0, 10);
	ss << " : ";
	ss << std::setfill('0') << std::setw(15) << std::fixed << elapsed.count();
	ss << " s ; ";
	ss << std::setfill(' ') << std::setw(30) << std::string(fichier, 0, 30);
	ss << " ; ";
	ss << std::setfill(' ') << std::setw(10) << std::string(ligne, 0, 10);
	ss << " -> ";
	ss << txt;

	std::cout << ss.str() << std::endl;

	if (!filename.empty())
	{
		std::ofstream os(filename, std::ios::app);
		os << ss.str() << std::endl;
	}
}
