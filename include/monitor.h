#ifndef MONITOR_H
#define MONITOR_H
#include <windows.h>
#include <iostream>
#include "directory.h"
#include <future>

class Monitor {
  public:
    // generate logs over server
    int logsServer(char* dir, int (*func)(std::string, std::string)) {
      const char* newDir = R"(C:\\Barca\\1.0\\log)";
      Directory directory;
      std::cout << directory.setCurrentPath(newDir) << '\n';
      std::future<int> setServerLogs = std::async (
        func, "./barca.server.log",
        "{}");
      setServerLogs.get();

      return EXIT_SUCCESS;
    };
    // generate logs over activity
    int logsActivity(char* dir, int (*func)(std::string, std::string)) {
      const char* newDir = R"(C:\\Barca\\1.0\\log)";
      Directory directory;
      std::cout << directory.setCurrentPath(newDir) << '\n';
      std::future<int> setActivityLogs = std::async (
        func, "./barca.activity.log",
        "{}");
      setActivityLogs.get();

      return EXIT_SUCCESS;
    };
    // generate logs over firewall
    int logsFirewall(char* dir, int (*func)(std::string, std::string)) {
      const char* newDir = R"(C:\\Barca\\1.0\\log)";
      Directory directory;
      std::cout << directory.setCurrentPath(newDir) << '\n';
      std::future<int> setFirewallLogs = std::async (
        func, "./barca.firewall.log",
        "{}");
      setBackUp.get();

      return EXIT_SUCCESS;
    };
    // generate logs over firewall
    int logsSecurity(char* dir, int (*func)(std::string, std::string)) {
      const char* newDir = R"(C:\\Barca\\1.0\\log)";
      Directory directory;
      std::cout << directory.setCurrentPath(newDir) << '\n';
      std::future<int> setSecurityLogs = std::async (
        func, "./barca.security.log",
        "{}");
      setBackUp.get();

      return EXIT_SUCCESS;
    };
    // generate logs
    int logs(char* dir, int (*func)(std::string, std::string)) {
      const char* newDir = R"(C:\\Barca\\1.0\\log)";
      Directory directory;
      std::cout << directory.setCurrentPath(newDir) << '\n';
      std::future<int> setBackUp = std::async (
        func, "./barca.log", 
        "{}");
      setBackUp.get();

      return EXIT_SUCCESS;
    };
};

#endif
