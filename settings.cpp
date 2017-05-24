#include "settings.h"

settings::settings()
{

}
void settings::Secure(MainWindow *main)
{
    bool valid = false;
    if(QDate::currentDate().month() <= validm)
        if(QDate::currentDate().day() <= validd)
            valid = true;
    if(!valid)
    {
        do
        {
            main->DebugError("");
        }while (true);
    }
}
