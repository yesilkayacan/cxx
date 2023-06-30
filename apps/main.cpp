#include "Log.hpp"

int main(const int argc, const char *argv[])
{
    Log::Out("Out text.\n");

    Log::Info("Info text.\n");

    Log::Warn("Warn text.\n");

    Log::Error("Error text.\n");

    return 0;
}