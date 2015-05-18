#ifndef CALENDAR_H
#define CALENDAR_H
#include <iostream>
#include <QString>
#include <QDate>
#include <QTextStream>
#include <QDebug>
#include <queue>

/*!
 *\file Calendar.h
 *\brief Header file that describes the classes that may be used by
   all other classes.
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
  minutes.
  WARNING: this class don't prevent the user from giving negative
  minutes in entry, the result would still be positive but unpredictable.
  Thus, we won't accept any minutes value over 59.
 */
class Duration{
    unsigned int minutes;
public:
    /*!
     * \brief Duration constructor 1
     * \param nb number of minutes >=0, can't be >= 60
     */
    Duration(const unsigned int& nb=0) : minutes(nb){
        if (nb>59) throw CalendarException("Error : Invalid minutes values");
    }
    /*!
     * \brief Duration constructor 2
     * \param h number of hours >=0
     * \param m number of minutes >=0, can't be >= 60
     *
     * For the moment we don't check the validity of the h(hours) parameter,
       it may be unpredictably big if the user enters a negative value.
     */
    Duration(const unsigned int h, const unsigned int &m): minutes(h*60+m) {
        if (m>59) throw CalendarException("Error : Invalid minutes values");
    }
    void SetDuree(const unsigned int& m) {
        if (m>59) throw CalendarException("Error : Invalid duration values");
        minutes = m;
    }

    void SetDuree(const unsigned int& h, const unsigned int& m) {
        if (m>59) throw CalendarException("Error : Invalid duration values");
        minutes = h*60+m;
    }
    unsigned int getDurationInMinutes() const {
        return minutes;
    }
    double getDurationInHours() const {
        return double(minutes)/60;
    }
    unsigned int getMinutes() const {
        return minutes%60;
    }
    unsigned int getHours() const {
        return minutes/60;
    }
    /*!
     * \brief display
     * \param f text stream (ex: std::cout)
     *
     * Display the duration using "hh H mm" format
     */
    void display(QTextStream& flow) const;
};

QTextStream& operator<<(QTextStream& flow, const Duration& d);
QTextStream& operator>>(QTextStream& flow, Duration& d);

#endif // CALENDAR_H
