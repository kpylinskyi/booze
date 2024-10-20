# Contributing

## Project structure

/booze
  ├── src             # Core C++ source code
  ├── include         # Header files
  ├── ui              # GTK UI
  ├── assets          # Images, icons, and other UI resources
  ├── test            # Unit tests
  ├── CMakeLists.txt  # Build configuration
  └── README.md       # Documentation


## Core Components

Homebrew’s CLI commands to fetch and manage packages:

- Install Package: `brew install <formula/cask>`
- Uninstall Package: `brew uninstall <formula/cask>`
- List Installed Packages: `brew list --formula` and `brew list --cask`
- Check for Updates: `brew outdated`
- Upgrade Packages: `brew upgrade`
- Cleanup: `brew cleanup`
- Package Insights `brew info <formula/cask>`
- Backup: Write installed packages to a text file using `brew list > backup.txt`
- Restore: Install packages using `brew install <file>`

#### Dependencies

- [Boost.Process](https://www.boost.org/doc/libs/1_64_0/doc/html/process.html) 
Install it with brew: `brew install boost`

3. Graphical User Interface (GUI)

#### Dependencies

- [GTK4](https://docs.gtk.org/gtk4/getting_started.html) 
Install it with brew: `brew install gtk4`

- [GTKMM4](https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/index.html) 
Install it with brew: `brew install gttkmm4`
