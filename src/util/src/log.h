#ifndef LOG_H
#define LOG_H

#include <string>
#include <cstdint>
#include <mutex>
#include "mutex.h"
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

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_LOG_DLL
#define LOG_DLL __declspec(dllexport)
#else
#define LOG_DLL __declspec(dllimport)
#endif
#else
#define LOG_DLL
#endif


class LOG_DLL Log
{
	private:
		std::mutex m_;
		std::string filename, filename_result;
		std::chrono::time_point<std::chrono::high_resolution_clock> t0;
Log()
{
	t0 = std::chrono::high_resolution_clock::now();
}



public:

static Log * getLogger()
{
	static Log * _instance = new Log();
	return _instance;
}

void setFileName(const std::string & fic1, const std::string & fic2)
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

void debug(const std::string & fichier, int32_t ligne, const std::string & txt)
{
	libre("DEBUG", fichier, std::to_string(ligne), txt);
}

void info(const std::string & fichier, int32_t ligne, const std::string & txt)
{
	libre("INFO", fichier, std::to_string(ligne), txt);
}

void warn(const std::string & fichier, int32_t ligne, const std::string & txt)
{
	libre("WARNING", fichier, std::to_string(ligne), txt);
}

void error(const std::string & fichier, int32_t ligne, const std::string & txt)
{
	libre("ERROR", fichier, std::to_string(ligne), txt);
}

void fatal(const std::string & fichier, int32_t ligne, const std::string & txt)
{
	libre("FATAL", fichier, std::to_string(ligne), txt);
}

void result(const std::string & fichier, const std::string & ligne, const std::string & OK_KO, const std::string & txt)
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

void libre(const std::string & type, const std::string & fichier, const std::string & ligne, const std::string & txt)
{
	Mutex mutex(m_);

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
};

#endif /* LOG_H */
