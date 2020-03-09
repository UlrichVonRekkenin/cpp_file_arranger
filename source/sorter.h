#ifndef SORT_DOWNLOAD_SORTER_H
#define SORT_DOWNLOAD_SORTER_H

#include <thread>
#include <map>
#include <set>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>


namespace tools {

namespace fs = std::filesystem;
using Rules = std::map<std::set<fs::path>, fs::path>;

class Sorter final {
  public:
    static void sort(const fs::path& dir_to_sort, const fs::path& output_dir, const fs::path& config_path = "")
    {
        static const auto rules = config_path.empty() ? Sorter::defaultRules() : Sorter::readConfig(config_path);

        auto action = [&output_dir](const fs::path& p) {
          const auto e{p.extension()};
          for (const auto&[exts, dest]: rules) {
              if (exts.find(e)!=exts.end()) {
                  const auto dir{output_dir/dest};
                  if (!fs::exists(dir)) fs::create_directories(dir);
                  std::cout << "Moving " << p << " to " << dir/p.filename() << std::endl;
                  fs::rename(p, dir/p.filename());
              }
          }
        };

        for (auto& it: fs::directory_iterator(dir_to_sort)) {
            if (!fs::is_directory(it) && !fs::is_symlink(it)) {
                std::thread th(action, it);
                th.join();
            }
        }
    }

  private:
    static auto readConfig(const fs::path& config_path) -> Rules
    {
        std::cout << "Got config_path " << config_path << " trying to parse it..." << std::endl;
        std::ifstream stream(config_path);

        Rules rules;
        std::string line;

        while (std::getline(stream, line)) {
            auto eraser = [&line](std::string_view delimiter) {
              std::vector<fs::path> result;
              std::size_t pos;
              std::string token;
              while ((pos = line.find(delimiter))!=std::string::npos) {
                  token = line.substr(0, pos);
                  line.erase(0, pos+delimiter.length());
                  result.emplace_back(token);
              }
              result.emplace_back(line);

              return result;
            };

            const auto value = eraser("::")[0];
            const auto exts = eraser(",");
            const std::set<fs::path> keys(exts.begin(), exts.end());

            rules[keys] = value;
        }

        std::cout << "Finish parsing " << config_path << ".\nGot " << rules.size() << " rules";
        return rules;
    }

    static auto defaultRules() -> Rules
    {
        std::cout << "Working with default rules" << std::endl;
        return {
                {{".jpg", ".png", ".jpeg", ".bmp", ".tiff"}, "Images"},
                {{".zip", ".tgz", ".rar", ".gz", ".7zxz", ".tar"}, "Archives"},
                {{".exe", ".deb", ".rpm", ".msi", ".whl", ".apk"}, "Programs"},
                {{".fb2", ".epub", ".djvu"}, "EBooks"},
                {{".torrent"}, "Torrent"},
                {{".py", ".pyw", ".sh"}, "Scripts"},
                {{".txt", ".doc", ".docx", ".pdf", ".xls", ".odt", ".ods", ".rtf", ".ppt"}, "Docs"},
                {{".mp3"}, "Audio"},
                {{".iso", ".nrg"}, "Iso"},
                {{".avi", ".mov", ".mp4", ".mkv", ".3gp", ".flv"}, "Video"},
                {{".tex", ".bib"}, "Docs/TeX"}
        };
    }
};

}

#endif //SORT_DOWNLOAD_SORTER_H
