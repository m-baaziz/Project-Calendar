#ifndef CALENDAR_H
#define CALENDAR_H
#include <iostream>"
#include <stack>
#include <map>
#include <QString>
#include <QDate>
#include <QFile>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QDebug>
#include <queue>
#include <QTime>

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
        //if (nb>59) throw CalendarException("Error : Invalid minutes values");
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
    void SetDuration(const unsigned int& m) {
        if (m>59) throw CalendarException("Error : Invalid duration values");
        minutes = m;
    }

    void SetDuration(const unsigned int& h, const unsigned int& m) {
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

    Duration operator+(const Duration& d) {
        return Duration(getHours()+d.getHours()+(getMinutes()+d.getMinutes())/60,(getMinutes()+d.getMinutes())%60);
    }
    QTime operator+(const QTime& t) const {
        return QTime(t.hour()+getHours(),t.minute()+getMinutes());
    }

    bool operator>(const Duration& d) const {
        return minutes>d.getDurationInMinutes();
    }
    bool operator<(const Duration& d) const {
        return minutes<d.getDurationInMinutes();
    }
    bool operator!=(const Duration& d) const {
        return getDurationInMinutes()!=d.getDurationInMinutes();
    }
    bool operator==(const Duration& d) const {
        return getDurationInMinutes()==d.getDurationInMinutes();
    }
    QString toString() const {
        unsigned int H = getHours();
        unsigned int M = getMinutes();
        QString h = (H<10)?"0"+QString::number(H):""+QString::number(H);
        QString m = (M<10)?"0"+QString::number(M):""+QString::number(M);
        return h+" H "+m;
    }
    Duration& fromString(const QString& d) {
        QStringList temp = d.split(" H ");
        if (temp[0]<0 || temp[1]<0) throw CalendarException("Error : wrong duration values given to Duration::fromString()");
        unsigned int H = temp[0].toInt();
        unsigned int M = temp[1].toInt();
        SetDuration(H,M);
        return *this;
    }
};

QTextStream& operator<<(QTextStream& flow, const Duration& d);
QTextStream& operator>>(QTextStream& flow, Duration& d);

#endif // CALENDAR_H
