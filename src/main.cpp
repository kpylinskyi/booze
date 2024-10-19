#include <gtkmm.h>         // For GTKmm (GUI)
#include <boost/process.hpp>  // For Boost.Process
#include <iostream>         // For standard I/O (to print messages)
#include <string>           // For std::string

namespace bp = boost::process;

class MyWindow : public Gtk::Window {
public:
    MyWindow() {
        // Set window properties
        set_title("Booze - Homebrew GUI");
        set_default_size(400, 200);

        // Configure button
        button.set_label("Install wget");  // The button text
        button.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked));

        // Add button to window
        set_child(button);  // `set_child()` is for GTK4 instead of `add()` (GTK3)

        // Show all children
        show_all();
    }

protected:
    // Button click callback
    void on_button_clicked() {
        // Use Boost.Process to run a Homebrew command (e.g., "brew install wget")
        try {
            // Output stream to capture the process output
            std::ostringstream output;

            // Run the command and capture the output
            bp::ipstream pipe_stream;  // Reading pipe for capturing the output
            bp::child c("brew install wget", bp::std_out > pipe_stream);

            std::string line;
            while (pipe_stream && std::getline(pipe_stream, line) && !line.empty()) {
                output << line << std::endl;
            }

            c.wait();  // Wait for the process to finish

            // Display a message dialog with the result
            Gtk::MessageDialog dialog(*this, "Homebrew Command Output", false, Gtk::MESSAGE_INFO);
            dialog.set_secondary_text(output.str());
            dialog.run();
        }
        catch (const std::exception &ex) {
            std::cerr << "Error executing process: " << ex.what() << std::endl;

            // Show error dialog in case of failure
            Gtk::MessageDialog error_dialog(*this, "Error", false, Gtk::MESSAGE_ERROR);
            error_dialog.set_secondary_text(ex.what());
            error_dialog.run();
        }
    }

private:
    Gtk::Button button;  // Button widget
};

int main(int argc, char *argv[]) {
    // Create a GTKmm application
    auto app = Gtk::Application::create("org.gtkmm.booze");

    // Create and run the main window
    MyWindow window;
    return app->make_window_and_run<MyWindow>(argc, argv);
}
