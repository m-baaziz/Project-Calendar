#ifndef CALENDAR_H
#define CALENDAR_H
#include <QString>
#include <QDate>
#include <QTextStream>

/*!
 *\file Calendar.h
 * Header file that describes the classes that may be used by
 * all other classes.
 */


using namespace std;

//! \brief manage error messages.
class CalendarException{
    QString info;
public:
    CalendarException(const QString& message):info(message){}
    QString getInfo() const { return info; }
};

/*!
 * \brief The Duration class
 *
 * Store durations only with minutes, but can be initialized
  with hours and minutes, and can be displayed in hours and
  minutes. We won't let the user set a negative number of minutes
  in order to avoid any unpredictable minutes value.
 */
class Duration{
    unsigned int minutes;
public:
    /*!
     * \brief Duration constructor 1
     * \param nb number of minutes >=0, can be >= 60
     */
    Duration(const unsigned int& nb=0) : minutes(nb){
        if (nb<0) throw CalendarException("Error : minutes number has to be positive");
    }
    /*!
     * \brief Duration constructor 2
     * \param h number of hours >=0
     * \param m number of minutes >=0, can't be >= 60
     */
    Duration(const unsigned int h, const unsigned int &m): minutes(h*60+m) {
        if (m>59 || m<0 || h<0) throw CalendarException("Error : Invalid duration values");
    }
    void SetDuree(const unsigned int& m) {
        if(m<0) throw CalendarException("Error : minutes number has to be positive");
        minutes = m;
    }
    void SetDuree(const unsigned int& h, const unsigned int& m) {
        if (m>59 || m<0 || h<0) throw CalendarException("Error : Invalid duration values");
        minutes = h*60+m;
    }
    unsigned int getDurationInMinutes() const {
        return minutes;
    }
    double getDurationInHours() const {
        return double(minutes)/60;
    }
    unsigned int getMinute() const {
        return minutes%60;
    }
    unsigned int getHours() const {
        return minutes/60;
    }
    void display(QTextStream& f) const;
};

#endif // CALENDAR_H
