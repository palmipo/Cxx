#ifndef LOG_H
#define LOG_H

#include <string>
#include <cstdint>
#include <mutex>

#if defined __MINGW32__ ||  defined __CYGWIN__
#ifdef MAKE_LOG_DLL
#define LOG_DLL __declspec(dllexport)
#else
#define LOG_DLL __declspec(dllimport)
#endif
#else
#define LOG_DLL
#endif


class LogMutex
{
    std::mutex &m_;

	public:
		LogMutex(std::mutex & m);
		~LogMutex();
};

class LOG_DLL Log
{
	public:
		static Log * getLogger();

		void setFileName(const std::string & fic1, const std::string & fic2);

		void debug(const std::string & fichier, int32_t ligne, const std::string &);
		void info(const std::string & fichier, int32_t ligne, const std::string &);
		void warn(const std::string & fichier, int32_t ligne, const std::string &);
		void error(const std::string & fichier, int32_t ligne, const std::string &);
		void fatal(const std::string & fichier, int32_t ligne, const std::string &);
		void result(const std::string & fichier, const std::string & ligne, const std::string & OK_KO, const std::string &);
		void libre(const std::string & type, const std::string & fichier, const std::string & ligne, const std::string &);

	private:
		Log();

		static Log * _instance;
		std::mutex m_;
		std::string filename, filename_result;
		std::chrono::time_point<std::chrono::high_resolution_clock> t0;
};

#endif /* LOG_H */
