"""
Created on 19.9.2012

@author: Chen Sheldon
"""
import os, time, core
from core import uitestcase

class SX_Helper(object):
    """
    This class holds global sx helper functions.

    """

    def __init__(self, phone):
        """

        """
        self.phone = phone

    def sxDeleteCalendarBySubject(self, subject):
        """Delete calendar items by subject
        Notice that all calendar items with the same name will be deleted in a row.
        """
        sxString = \
        """
        (load* "apps/calendar-evo/calendar-model")
        (debug "got there 12345")
        (define/mutable (granite-delete-calendar-items-by-subject subject callback)
            (define loader (serializable-loader 'calendar-item))
            (send loader where (string-append "\\"subject\\" = \\"" (if (number? subject) (number->string subject) else subject) "\\""))
            (send loader load-items
                (lambda (i)
                    (debug "Got item id: "(send i get-id))
                    (send global-calendar-model get-item-by-id (send i get-id)
                        (lambda (loaded-item)
                            (send global-calendar-model delete-item loaded-item)
                        )
                    )
                )
                (lambda ()
                    (callback)
                )
            )
        )
        (granite-delete-calendar-items-by-subject "%s"
            (lambda ()
                (debug "Item deleted.")
            )
        )
        """ % (subject)
        self.phone.sx(sxString)
        self.phone.delay(1000)

    def sxDeleteCalendarItemBeforeDate(self, date=(2020, 1, 1, 1, 0, 0)):
        """Delete calendar items before specified datetime(yy-mm-dd-hh-mm-ss)
        It also could be used as DeleteAll function.
        """
        sxString = \
        """
        (define/mutable (granite-delete-calendar-items-before-date date)
            (load* "apps/calendar-evo/calendar-model")
            (send global-calendar-model remove-items-before-date date)
        )

        (define/mutable granite-temp-time (create-builtin-date-time))
        (send granite-temp-time set-datetime
            %s
            %s
            %s
            %s
            %s
            %s
            'local
        )
        (granite-delete-calendar-items-before-date granite-temp-time)
        """ % (date[0], date[1], date[2], date[3], date[4], date[5])
        self.phone.sx(sxString)
        self.phone.delay(1000)

    def sxAddCalendarItem(self, subject='test', description='', location='', \
                        startTime=(2012, 10, 20, 6, 20, 0), reminderTime=1, type='false', \
                        missedFlag=0, priority=2, completedDate='', recurrence='', duration=120,
                        repeatend=(2012, 10, 20, 6, 20, 0)):
        """Add one calendar item
        subject # ; Subject/Occasion/Name.
        description # ; Description
        location # ; Location/completed-dates.
        startTime # ; Start date/time.
        reminderTime # ; Alert seconds before.
        type # ; event type, false is appointment, true is birthday (whole day event)
        recurrence # ; Recurrence(once/weekly...) vaild input "" "RRULE:D1 #0" "RRULE:W1 #0" "RRULE:MD1 #0" "RRULE:MD12 #0"
        duration # ; Use this to set end time (end time = start time + duration(seconds))
        repeatend # ; Used for customizing the recurrence finish date.
        """
        defaultDict = { 'subject': subject, \
                        'description': description, \
                        'location': location, \
                        'startTime': startTime, \
                        'reminderTime': reminderTime, \
                        'type': type, \
                        'missedFlag': missedFlag, \
                        'priority': priority, \
                        'completedDate': completedDate, \
                        'recurrence': recurrence, \
                        'duration': duration, \
                        'repeatend': repeatend}
        sxString = \
        """
        (load* "apps/calendar-evo/calendar-model")
        (define/mutable (granite-add-calendar-item)

            (define start (create-builtin-date-time))
            (define repeatend (create-builtin-date-time))
            (define end (create-builtin-date-time))
            (define duration 0)
            (define new-item (calendar-item))

            (send new-item set-subject "%s")      ; Enter subject.
            (send new-item set-description "%s")
            (send new-item set-location "%s")         ; Enter subject.
            (send new-item set-start start)         ; Give start time. See below for correct format.
            (send new-item set-end end)             ; Suggest not set there. Use duration to set the end time.
            (send new-item set-reminder-time %s)     ; Alert seconds before.
            (send new-item set-type %s)              ; event type, false is appointment, true is birthday (whole day event)
            (send new-item set-missed-flag %s)
            (send new-item set-priority %s)          ; vCal priority
            (send new-item set-completed-date "%s")
            (send new-item set-recurrence "%s")       ; Repeat time.
            (send new-item set-repeat-end repeatend)  ; Give repeat end time. See below for correct format.
            (debug "got there!!!: ")
            (send start set-datetime
                %s
                %s
                %s
                %s
                %s
                %s
                'local
            )
            (send new-item set-duration %s)
            (send repeatend set-datetime
                %s
                %s
                %s
                %s
                %s
                %s
                'local
            )

            new-item
        )
        (send global-calendar-model save-item (granite-add-calendar-item) false
            (lambda (item)
                (debug "Calendar item added.")
            )
        )
        """ % (defaultDict['subject'], defaultDict['description'], defaultDict['location'], defaultDict['reminderTime'], defaultDict['type'], defaultDict['missedFlag'],
        defaultDict['priority'], defaultDict['completedDate'], defaultDict['recurrence'], defaultDict['startTime'][0], defaultDict['startTime'][1], defaultDict['startTime'][2],
        defaultDict['startTime'][3], defaultDict['startTime'][4], defaultDict['startTime'][5], defaultDict['duration'], defaultDict['repeatend'][0], defaultDict['repeatend'][1],
        defaultDict['repeatend'][2], defaultDict['repeatend'][3], defaultDict['repeatend'][4], defaultDict['repeatend'][5])

        self.phone.sx(sxString)
        self.phone.delay(1000)

    def sxAddPhoneContact(self, setBdayFlag='false', bday=(2012, 10, 20, 6, 20, 0), firstname='test', \
                        lastname='', nickname='', title='', org='', categories='', note='', \
                        phone1='', phone2='', phone3='', phone4=''):
        """Add one phone contact item
        'set-bday?': Flag to control if you want to set bday(birthday)
        'bday': Birthday. Time format.(yy-mm-dd-hh-mm-ss)
        'firstname': First name of new contact.
        'lastname': Last name of new contact.
        'nickname':
        'title': job-title
        'org': company
        'categories':
        'note':
        'phone1': Mobile number
        'phone2': Home number
        'phone3': Work number
        'phone4': Other number
        """
        defaultDict = { 'set-bday?': setBdayFlag, \
                        'bday': bday, \
                        'firstname': firstname, \
                        'lastname': lastname, \
                        'nickname': nickname, \
                        'title': title, \
                        'org': org, \
                        'categories': categories, \
                        'note': note, \
                        'phone1': phone1, \
                        'phone2': phone2, \
                        'phone3': phone3, \
                        'phone4': phone4}
        sxString = \
        """
        (load* "apps/contacts/contact-database")
        (define/mutable (granite-add-phone-contact)
            (define new-item (contact-object))
            (define set-bday? %s)
            (when set-bday?
                (define bday (create-builtin-date-time))
                (send bday set-datetime
                    %s
                    %s
                    %s
                    %s
                    %s
                    %s
                    'local
                )
                (send new-item set-value! 'bday bday)
            )

            (send new-item set-value! 'firstname "%s")
            (send new-item set-value! 'lastname "%s")
            (send new-item set-value! 'nickname "%s")
            (send new-item set-value! 'photo false)
            (send new-item set-value! 'title "%s")
            (send new-item set-value! 'org "%s")
            (send new-item set-value! 'categories "%s")
            (send new-item set-value! 'note "%s")
            (send new-item set-value! 'anniversary false)

            (send new-item set-value! 'number:phone1:number "%s")
            (send new-item set-value! 'number:phone2:number "%s")
            (send new-item set-value! 'number:phone3:number "%s")
            (send new-item set-value! 'number:other:number "%s")

            (send new-item save-contact true false
                (lambda (success?)
                    (debug "New contact done!!!!!!!!!!" success?)
                )
            )
        )
        (granite-add-phone-contact)
        """ % (defaultDict['set-bday?'], \
            defaultDict['bday'][0], defaultDict['bday'][1], defaultDict['bday'][2], defaultDict['bday'][3], defaultDict['bday'][4], defaultDict['bday'][5], \
            defaultDict['firstname'], \
            defaultDict['lastname'], \
            defaultDict['nickname'], \
            defaultDict['title'], \
            defaultDict['org'], \
            defaultDict['categories'], \
            defaultDict['note'], \
            defaultDict['phone1'], \
            defaultDict['phone2'], \
            defaultDict['phone3'], \
            defaultDict['phone4'])
        self.phone.sx(sxString)
        self.phone.delay(1000)

    def sxAddSIMContact(self, setBdayFlag='false', bday=(2012, 10, 20, 6, 20, 0), firstname='test', \
                        lastname='', nickname='', title='', org='', categories='', note='', \
                        phone1='', phone2='', phone3='', phone4='',sim_slot=0):
        """Add one SIM contact item, store in sim1 or sim in default
        'set-bday?': Flag to control if you want to set bday(birthday)
        'bday': Birthday. Time format.(yy-mm-dd-hh-mm-ss)
        'firstname': First name of new contact.
        'lastname': Last name of new contact.
        'nickname':
        'title': job-title
        'org': company
        'categories':
        'note':
        'phone1': Mobile number
        'phone2': Home number
        'phone3': Work number
        'phone4': Other number
        'sim_slot':0 means sim1(DS) or sim memory(SS); 1 means sim2 memory
        """
        defaultDict = { 'set-bday?': setBdayFlag, \
                        'bday': bday, \
                        'firstname': firstname, \
                        'lastname': lastname, \
                        'nickname': nickname, \
                        'title': title, \
                        'org': org, \
                        'categories': categories, \
                        'note': note, \
                        'phone1': phone1, \
                        'phone2': phone2, \
                        'phone3': phone3, \
                        'phone4': phone4, \
                        'sim_slot':sim_slot}
        sxString = \
        """
        (load* "apps/contacts/contact-database")
        (define/mutable (granite-add-phone-contact)
            (define new-item (contact-object))
            (define set-bday? %s)
            (when set-bday?
                (define bday (create-builtin-date-time))
                (send bday set-datetime
                    %s
                    %s
                    %s
                    %s
                    %s
                    %s
                    'local
                )
                (send new-item set-value! 'bday bday)
            )

            (send new-item set-value! 'firstname "%s")
            (send new-item set-value! 'lastname "%s")
            (send new-item set-value! 'nickname "%s")
            (send new-item set-value! 'photo false)
            (send new-item set-value! 'title "%s")
            (send new-item set-value! 'org "%s")
            (send new-item set-value! 'categories "%s")
            (send new-item set-value! 'note "%s")
            (send new-item set-value! 'anniversary false)
            (send new-item set-value! 'sim-slot %s)
            (send new-item set-value! 'type 'sim)

            (send new-item set-value! 'number:phone1:number "%s")
            (send new-item set-value! 'number:phone2:number "%s")
            (send new-item set-value! 'number:phone3:number "%s")
            (send new-item set-value! 'number:other:number "%s")

            (send new-item save-contact true false
                (lambda (success?)
                    (debug "New contact done!!!!!!!!!!" success?)
                )
            )
        )
        (granite-add-phone-contact)
        """ % (defaultDict['set-bday?'], \
            defaultDict['bday'][0], defaultDict['bday'][1], defaultDict['bday'][2], defaultDict['bday'][3], defaultDict['bday'][4], defaultDict['bday'][5], \
            defaultDict['firstname'], \
            defaultDict['lastname'], \
            defaultDict['nickname'], \
            defaultDict['title'], \
            defaultDict['org'], \
            defaultDict['categories'], \
            defaultDict['note'], \
            defaultDict['sim_slot'], \
            defaultDict['phone1'], \
            defaultDict['phone2'], \
            defaultDict['phone3'], \
            defaultDict['phone4'])
        self.phone.sx(sxString)
        self.phone.delay(1000)

    def sxDeleteContactByFirstname(self, firstname):
        """Delete contact items by firstname
        Notice that all contact items with the same firstname will be deleted in a row.
        """
        sxString = \
        """
        (load* "apps/contacts/contact-database")
        (define/mutable (granite-delete-contact-by-first-name first-name)
            (define loader (serializable-loader 'contact-object))
            (send loader where (string-append "\\"firstname\\" = \\"" (if (number? first-name) (number->string first-name) else first-name) "\\""))
            (send loader set-supply-item-function (lambda (k v) (contact-object)))
            (send loader load-items
                (lambda (i)
                    (debug "Got item id: "(send i get-id))
                    (send i delete
                        (lambda (success?)
                            (debug "Delete compeleted!" success?)
                        )
                    )
                )
                (lambda ())
            )
        )
        (granite-delete-contact-by-first-name "%s")
        """ % (firstname)
        self.phone.sx(sxString)
        self.phone.delay(1000)

    def sxDeleteAllContact(self):
        """Delete all contact items
        Some sim contacts may not be deleted.
        """
        sxString = \
        """
        (load* "apps/contacts/contact-database")
        (define/mutable (granite-delete-all-contact)
            (define loader (serializable-loader 'contact-object))
            (define loaded-items '())
            (send loader load-items
                (lambda (i)
                    (debug "Got item id: "(send i get-id))
                    (set! loaded-items (append loaded-items (list (send i get-id))))
                )
                (lambda ()
                    (send (get-contacts-database-api) delete-contacts loaded-items
                        (lambda (success?)
                            (debug "Delete compeleted!" success?)
                        )
                    )
                )
            )
        )
        (granite-delete-all-contact)
        """
        self.phone.sx(sxString)
        self.phone.delay(1000)

    def sxInsertCounterItem(self, type, duration, simRef = "0"):
        """Insert counter item
        'type: "call-mo", "call-mt", "sms-sent", "sms-received", "mms-sent", "mms-received", "traffic"
        'duration: for call-mo/mt: "60" (seconds)
                   for sms/mms: "1" (messages)
        'simRef: "0" or "1"
                 "0" for sim1;
                 "1" for sim2
        """
        sxString = \
        """
        (define/mutable (granite-insert-counter-item type duration)
            (define/mutable imsi (send (get-sim-manager %s) get-imsi))
            (define/mutable timestamp (create-time))
            (send (get-data-counter-database-api) insert-counter-item type imsi timestamp duration)
        )
        (granite-insert-counter-item '%s %s)
        """ % (str(simRef), str(type), str(duration))
        self.phone.sx(sxString)
        self.phone.delay(1000)

    def sxRemoveCounterItem(self, type, simRef = "0"):
        """Remove counter item
        'type: "call-mo", "call-mt", "sms-sent", "sms-received", "mms-sent", "mms-received", "traffic"
        'simRef: "0" or "1"
                 "0" for sim1;
                 "1" for sim2
        """
        sxString = \
        """
        (load* "apps/data-traffic-counter/data-traffic-counter-manager")
        (define/mutable (granite-remove-counter-item type)
            (define/mutable imsi (send (get-sim-manager %s) get-imsi))
            (define/mutable date-range (send data-counter-manager get-date-range imsi 0))
            (send (get-data-counter-database-api) remove-counter-items type imsi (list-ref date-range 0)  (list-ref date-range 1))
        )
        (granite-remove-counter-item '%s)
        """ % (str(simRef), str(type))
        self.phone.sx(sxString)
        self.phone.delay(1000)\

    def sxRemoveAllCounterItems(self, simRef = "0"):
        """Remove all types counter item
        'simRef: "0" or "1"
                 "0" for sim1;
                 "1" for sim2
        """
        sxString = \
        """
        (load* "apps/data-traffic-counter/data-traffic-counter-manager")
        (define/mutable (granite-remove-counter-item type)
            (define/mutable imsi (send (get-sim-manager %s) get-imsi))
            (define/mutable date-range (send data-counter-manager get-date-range imsi 0))
            (send (get-data-counter-database-api) remove-counter-items type imsi (list-ref date-range 0)  (list-ref date-range 1))
        )
        (granite-remove-counter-item 'traffic)
        (granite-remove-counter-item 'call-mo)
        (granite-remove-counter-item 'call-mt)
        (granite-remove-counter-item 'sms-sent)
        (granite-remove-counter-item 'sms-received)
        (granite-remove-counter-item 'mms-sent)
        (granite-remove-counter-item 'mms-received)
        """ % (str(simRef))
        self.phone.sx(sxString)
        self.phone.delay(1000)

    def _sxAddAlarmClock(self, alarmtime=(12, 1), days=[], snoozeTime=120, date=(2013, 1, 1)):
        """
            Example / Description:
                alarmtime   :   (Hour, Minute)
                snoozeTime  :   Seconds
                days        :   [1, 2, 3, 4, 5, 6, 7]
        """
        DaySymbol   = {
            1   : "'mon",
            2   : "'tue",
            3   : "'wed",
            4   : "'thu",
            5   : "'fri",
            6   : "'sat",
            7   : "'sun",
        }

        daySymbolList   = ''
        if days:
            daySymbolList   = ' '.join(map(lambda x: DaySymbol[x], days))

        sxString = \
        """
        (load* "apps/alarmclock/alarmclock-database")
        (define/mutable (granite-add-alarmclock)
            (define new-item (alarmclock-item))
            (define alarm-time (create-builtin-date-time))
            (send alarm-time set-datetime
                %i
                %i
                %i
                %i
                %i
                0
                'local
            )
            (send new-item set-alarm-time alarm-time)
            (send new-item set-days (list %s))
            (send new-item set-snooze-time %i)
            (send new-item set-snooze-repeat 10)

            (send (get-alarmclock-database-api) add-alarm new-item false
                (lambda (success?)
                    (debug "New alarmclock done!!!!!!!!!!" success?)
                )
            )
        )
        (granite-add-alarmclock)
        """ % ( date + alarmtime + ( daySymbolList, snoozeTime) )
        self.phone.sx(sxString)
        self.phone.delay(500)

    def _sxClearAllAlarmClock(self):
        """
        """
        sxString = """(send (get-alarmclock-database-api) delete-all-alarms
            (lambda (success?)
                (debug "Clear alarmclock done!!!!!!!!!!" success?)
            )
        )"""
        self.phone.sx(sxString)

    def _sxAddCallLog(self, number, starttime=(2013, 2, 1, 10, 0, 0), endtime=(2013, 2, 1, 10, 0, 30), sim=1, type='missed'):
        """
        """
        typeDict    = {
            'missed'    :   "'calllog-missed",
            'dialed'    :   "'calllog-dialed",
            'received'  :   "'calllog-received",
        }
        setStartTime    = """
            (send start-time set-datetime
                %i
                %i
                %i
                %i
                %i
                %i
                'local
            )
            (send new-item set-start-time start-time)
        """ % starttime

        setEndTime      = ""
        if endtime:
            setEndTime  = """
                (send end-time set-datetime
                    %i
                    %i
                    %i
                    %i
                    %i
                    %i
                    'local
                )
                (send new-item set-end-time end-time)
            """ % endtime

        sxString    = """
        (load* "apps/calllog/calllog-database")
        (define/mutable (granite-add-calllog number)
            (define new-item (calllog-item))
            (define num number)
            (define stripped-num (strip-number num))
            (define start-time (create-builtin-date-time))
            (define end-time (create-builtin-date-time))
            %s
            %s
            (send new-item set-sim-slot %i)
            (send new-item set-type %s)
            (when (and (string? num) (= (string-length num) 0))
                (set! num "hidden")
                (set! stripped-num "hidden")
            )
            (send new-item set-phone-number num)
            (send new-item set-value! 'stripped-number stripped-num)
            (send (get-calllog-database-api) save-call new-item)
        )
        (granite-add-calllog "%s")
        """ % (setStartTime, setEndTime, sim-1, typeDict[type], str(number))

        self.phone.sx(sxString, doNotReport=True)
        self.phone.delay(1000)

    def _sxClearCallLog(self):
        """
        """
        sxString    = """(begin
            (send (get-calllog-database-api) delete-all-calls 'calllog-missed (lambda ()
                    (debug "Clear all missed calllog"
                    )
                )
            )

            (send (get-calllog-database-api) delete-all-calls 'calllog-dialed (lambda ()
                        (debug "Clear all dialed calllog"
                    )
                )
            )

            (send (get-calllog-database-api) delete-all-calls 'calllog-received (lambda ()
                        (debug "Clear all received calllog"
                    )
                )
            )

            (define ntfApp (send (get-app-manager) invoke-uri "x-notification-manager"))

            (send ntfApp remove-all-visible-notifications)
        )
        """

        self.phone.sx(sxString, doNotReport=True)
        self.phone.delay(500)

    def _sxClearMessages(self):
        """
        """
        sxString    = """(begin
            (send msg-db-access delete-all-conversations (lambda (isSuccess)
                    (if isSuccess
                        (debug "SX Helper: Remove all conversations!")
                        (debug "SX Helper: Failed to remove conversations")
                    )
                )
            )
            (define ntfApp (send (get-app-manager) invoke-uri "x-notification-manager"))
            (send ntfApp remove-all-visible-notifications)
        )
        """
        self.phone.sx(sxString, doNotReport=True)
        self.phone.delay(1000)

    def _sxAddNotes(self, text, createdate=(2012, 1, 1, 12, 0, 0), modifydate=(2012, 1, 1, 12, 0, 0)):
        """
        """
        setDateTime    = """
            (send created-time set-datetime
                %i
                %i
                %i
                %i
                %i
                %i
                'local
            )
            (send modified-time set-datetime
                %i
                %i
                %i
                %i
                %i
                %i
                'local
            )
            (send new-item set-date modified-time)
            (send new-item set-value! 'date-created created-time)
        """ % (createdate + modifydate)
        sxString    = """(begin
            (load* "apps/notes/notes-database")

        (define/mutable (on-note-save-call-back . args)
            (case (length args)
                ((0)
                    (debug "Granite SX: Create new note!")
                )
                ((1)
                    (debug "Granite SX: Fail to create new note!")
                )
            )
        )

        (define/mutable (granite-add-notes)
            (define new-item (notes-object))
            (define created-time (create-builtin-date-time))
            (define modified-time (create-builtin-date-time))
            %s
            (send new-item set-body "%s")

            (send new-item save false on-note-save-call-back)
        )
        (granite-add-notes)
        )
        """ % (setDateTime, text)

        self.phone.sx(sxString, doNotReport=True)
        self.phone.delay(500)

    def _sxDeleteAllNotes(self):
        """
        """
        sxString    = """(begin
            (define temp-notes-model (notes-model))

            (send temp-notes-model delete-all-notes (lambda () debug "Granite SX: Removing all notes complete."))
        )
        """

        self.phone.sx(sxString, doNotReport=True)
        self.phone.delay(500)

    def setOnOffBluetooth(self, active):
        """
            Example / Description: Switch on/off Bluetooth
            Parameters:
                active/string type    :    'true'/'flase'
        """
        sxString = \
        """
        (begin
            (send (get-bluetooth-manager) set-active %s)
        )
        """ % (active)

        self.phone.sx(sxString)
        self.phone.delay(1000)

    def setOnOffWifi(self, active):
        """
            Example / Description: Switch on/off Wifi
            Parameters:
                active/string type    :    'true'/'flase'
        """
        sxString = \
        """
        (begin
            (send (get-wlan-manager) set-active %s)
        )
        """ % (active)

        self.phone.sx(sxString)
        self.phone.delay(1000)

    def setOnOffSilentMode(self, active):
        """
            Example / Description: Switch on/off Slient mode
            Parameters:
                active/string type    :    'true'/'flase'
        """
        sxString = \
        """
        (begin
            (send config-manager set-setting "./yapas/sound/silent" %s)
        )
        """ % (active)

        self.phone.sx(sxString)
        self.phone.delay(1000)

    def getBacklightBrightness(self):
        """
            Example / Description: Get phone screen backlight brightness
            return/int type    :    Brightness level
        """
        sxString = \
        """
        (begin
            (send (get-lcd-manager) get-backlight-level)
        )
        """
        level = self.phone.sx(sxString, convertToString=True)
        self.phone.delay(1000)
        return int(level)

    def getFreeSpace(self, type):
        """
            Example / Description: Get phone memory or MMC memory free space.
            Parameters:
                type/string type    :    "\'phone" / "\'mmc"
            return/int type    :    The size of free space(KB).
        """
        sxString = \
        """
        (begin
            (define/mutable (granite-get-free-pace type)
                (case type
                    ((phone)
                        (send (get-file-system-manager) get-file-system-capacity "file:///usr/_phone" 'free)
                    )
                    ((mmc)
                        (send (get-file-system-manager) get-file-system-capacity "file:///usr/_memory_card" 'free)
                    )
                )
            )
            (granite-get-free-pace %s)
        )
        """ % (type)
        size = self.phone.sx(sxString, convertToString=True)
        self.phone.delay(1000)
        return int(size)

    def setToBatteryLow(self):
        """
            Example / Description: Disconnect charger, and set to battery low. To popup battery low dialog.
        """
        sxString = \
        """
        (begin
            (define battery-manager (get-battery-manager))
            (define automation-manager (get-automation-manager))
            (define (disconnect-charger)
                (define disconnnected #f)
                (define em-charger-status-data 0x00)
                (define em-charger-disconnected 0x00)
                (send automation-manager send-em-info-ind em-charger-status-data em-charger-disconnected)
                (wait 1000
                    (lambda ()
                        (set! disconnnected (send battery-manager is-charger-inserted))
                        (debug "is-charger-inserted: " disconnnected)
                    )
                )
            )

            (define (set-charging-state-off)
                (define charging-state #f)
                (define em-charging-state-data 0x13)
                (define em-charging-state-off 0x01)
                (send automation-manager send-em-info-ind em-charging-state-data em-charging-state-off)
                (wait 1000
                    (lambda ()
                        (set! charging-state (send battery-manager is-charging))
                        (debug "is-charging: " charging-state)
                    )
                )
            )

            (define (set-battery-to-low)
                (define batt-state #f)
                (define em-monitoring-batt-power-data 0x15)
                (define em-monitoring-batt-low 0x02)
                (send automation-manager send-em-info-ind em-monitoring-batt-power-data em-monitoring-batt-low)
                (wait 1000
                    (lambda ()
                        (set! batt-state (send battery-manager is-low-battery))
                        (debug "is-low-battery: " batt-state)
                        (if batt-state
                            (debug "set battery to low state succeeded!")
                            (debug "set battery to low state failed!")
                        )
                    )
                )
            )
            (disconnect-charger)
            (set-charging-state-off)
            (set-battery-to-low)
        )
        """
        self.phone.sx(sxString)
        self.phone.delay(3000)

    def setToBatteryNormal(self):
        """
            Example / Description: Connect charger, and set to battery OK.
        """
        sxString = \
        """
        (begin
            (define battery-manager (get-battery-manager))
            (define automation-manager (get-automation-manager))
            (define (connect-charger)
                (define connnected #f)
                (define em-charger-status-data 0x00)
                (define em-charger-connected 0x01)
                (send automation-manager send-em-info-ind em-charger-status-data em-charger-connected)
                (wait 1000
                    (lambda ()
                        (set! connnected (send battery-manager is-charger-inserted))
                        (debug "is-charger-inserted: " connnected)
                    )
                )
            )

            (define (set-charging-state-on)
                (define charging-state #f)
                (define em-charging-state-data 0x13)
                (define em-charging-state-on 0x02)
                (send automation-manager send-em-info-ind em-charging-state-data em-charging-state-on)
                (wait 1000
                    (lambda ()
                        (set! charging-state (send battery-manager is-charging))
                        (debug "is-charging: " charging-state)
                    )
                )
            )

            (define (set-battery-to-ok)
                (define batt-state #f)
                (define em-monitoring-batt-power-data 0x15)
                (define em-monitoring-batt-ok 0x01)
                (send automation-manager send-em-info-ind em-monitoring-batt-power-data em-monitoring-batt-ok)
                (wait 1000
                    (lambda ()
                        (set! batt-state (send battery-manager is-low-battery))
                        (debug "is-low-battery: " batt-state)
                    )
                )
            )
            (connect-charger)
            (set-charging-state-on)
            (set-battery-to-ok)
        )
        """
        self.phone.sx(sxString)
        self.phone.delay(3000)

    def sxCreateAndSetIap(self,sim_slot=0,name='iop'):
        """
            Create Access Point iop and set to iop for BTN, in case of facebook twitter cannot login
        """
        defaultDict = { 'sim_slot': sim_slot, \
                        'name': name}
        sxString = \
        """
        (define/mutable (create-and-set-iap)
            ;-------------- user defined value ------------
            ; SIM SLOT - 0 for SIM1, 1 for SIM2
            (define sim-slot %s)
            ; ConRef - Access Point to be selected.
            ; In below example "IPv4_TRELTE_COM" is the name of selected AP.
            (define conRef #d(("ConRef" "BTN_NAP") ("Type" "Nap")))
            ; PortNbr - Port Number
            (define PortNbr "8080")
            ; Addr - Proxy server
            (define Addr "195.134.224.45")
            ; Name - Proxy Name
            (define Name "%s")
            ;-------------- user defined value ------------
            (define sim-id (send (get-sim-manager sim-slot) get-sim-id))
            (define iap-edit-model (create-cp-iap-edit-model
                                    'mode 'create
                                    'sim-id sim-id
                                    'type "Proxy"))
            ;; Create iap.
            (send iap-edit-model set-value! "ConRef" conRef)
            (send iap-edit-model set-value! "PortNbr" PortNbr)
            (send iap-edit-model set-value! "Addr" Addr)
            (send iap-edit-model set-value! "Name" Name)
            (debug "####### Valid?: " (send iap-edit-model valid?))
            (send iap-edit-model update-iap)
            ;; Set created iap to default.
            (define iap-list-model (create-cp-iap-list-model sim-id))
            (define key false)
            (define (set-iap-to-default iap-list)
                (when (not (null? iap-list))
                    (set! key (list-ref iap-list 0))
                    (set! iap-list (list-tail iap-list 1))
                    (debug "##############: " key)
                    (if (equal? (dictionary-ref key "Name") Name)
                        (send iap-list-model set-default-iap (dictionary-ref key "UId"))
                        (set-iap-to-default iap-list)
            )))
            (set-iap-to-default (send (get-cp-api) get-prov-setting (string-append "./Prov/" sim-id "/IAP")))
        )
        ; Execute function
        (create-and-set-iap)
        """ % (defaultDict['sim_slot'], defaultDict['name'])
        self.phone.sx(sxString)
        self.phone.delay(1000)

    def sxSetDefaultIap(self,sim_slot=0,name='btn nap'):
        """
            Set to default BTN Nap, usually use in tearDown to set to default
        """
        defaultDict = { 'sim_slot': sim_slot, \
                        'name': name}
        sxString = \
        """
        (define/mutable (change-iap)
            ;-------------- user defined value ------------
            ; SIM SLOT - 0 for SIM1, 1 for SIM2
            (define sim-slot %s)
            ; Name - AP Name
            (define Name "%s")
            ;-------------- user defined value ------------
            (define sim-id (send (get-sim-manager sim-slot) get-sim-id))
            ;; Set created iap to default.
            (define iap-list-model (create-cp-iap-list-model sim-id))
            (define key false)
            (define (set-iap-to-default iap-list)
                (when (not (null? iap-list))
                    (set! key (list-ref iap-list 0))
                    (set! iap-list (list-tail iap-list 1))
                    (debug "##############: " key)
                    (if (equal? (dictionary-ref key "Name") Name)
                        (send iap-list-model set-default-iap (dictionary-ref key "UId"))
                        (set-iap-to-default iap-list)
            )))
            (set-iap-to-default (send (get-cp-api) get-prov-setting (string-append "./Prov/" sim-id "/IAP")))
        )
        ; Execute function
        (change-iap)
        """ % (defaultDict['sim_slot'], defaultDict['name'])
        self.phone.sx(sxString)
        self.phone.delay(1000)

    def sxDeleteIap(self,sim_slot=0,name='iop'):
        """
            Delete the newly created access point iop 
        """
        defaultDict = { 'sim_slot': sim_slot, \
                        'name': name}
        sxString = \
        """
        (define/mutable (delete-iap)
            ;-------------- user defined value ------------
            ; SIM SLOT - 0 for SIM1, 1 for SIM2
            (define sim-slot %s)
            ; Name - AP Name
            (define Name "%s")
            ;-------------- user defined value ------------
            (define sim-id (send (get-sim-manager sim-slot) get-sim-id))
            (define key false)
            (define (delete-iap-by-name iap-list name)
                (when (not (null? iap-list))
                    (set! key (list-ref iap-list 0))
                    (set! iap-list (list-tail iap-list 1))
                    (if (equal? (dictionary-ref key "Name") name)
                        (send (get-cp-api) delete-prov-setting (string-append "./Prov/" sim-id "/IAP" "/" (dictionary-ref key "UId")))
                        (delete-iap-by-name iap-list name)
            )))
            (delete-iap-by-name (send (get-cp-api) get-prov-setting (string-append "./Prov/" sim-id "/IAP")) Name)
        )
        ; Execute function
        (delete-iap)
        """ % (defaultDict['sim_slot'], defaultDict['name'])
        self.phone.sx(sxString)
        self.phone.delay(1000)