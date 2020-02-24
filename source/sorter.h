#ifndef SORT_DOWNLOAD_SORTER_H
#define SORT_DOWNLOAD_SORTER_H

#include <thread>
#include <map>
#include <set>
#include <filesystem>
#include <iostream>


class Sorter final {
  public:
    static void sort(const std::filesystem::path& dir_to_sort, const std::filesystem::path& output_dir)
    {
        namespace fs = std::filesystem;
        using Rules = std::map<std::set<fs::path>, fs::path>;

        static const Rules rules = {
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

        auto action = [&output_dir](const fs::path& p) {
          const auto e{p.extension()};
          for (const auto&[exts, dest]: rules) {
              if (exts.find(e)!=exts.end()) {
                  const auto dir{output_dir/dest};
                  fs::create_directories(dir);
                  std::cout << "Moving " << p << " to " << dir/p.filename() << std::endl;
                  fs::rename(p, dir/p.filename());
              }
          }
        };

        for (auto& p: fs::directory_iterator(dir_to_sort)) {
            if (!fs::is_directory(p) && !fs::is_symlink(p)) {
                std::thread th(action, p);
                th.join();
            }
        }
    }
};

#endif //SORT_DOWNLOAD_SORTER_H
