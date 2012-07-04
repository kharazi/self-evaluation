import os, sys, getopt, sqlite3, datetime

conn = sqlite3.connect('/home/s1na/self-evaluation/selfeval.db')
c = conn.cursor()

def errorExit(s):
    sys.stderr.write(s+'\n')
    sys.exit(1)

def help():
    print "The purpose of this application is collecting one's actions through a period of time and analyzing it in different ways."
    print "Commands: "
    print "help    : to view this help page"
    print "addaction    : to add an action. options are -t (action type id) -d (description) -r (rate)"
    print "listactions    : to list all the actions"
    print "listtypes    : to list all of the action types"
    print "listusers    : to list all of the users"
    print "adduser    : to add a user"

def getOptsArgs(shortOptions, longOptions):
    try:
        return getopt.gnu_getopt(sys.argv[2:], shortOptions, longOptions)
    except getopt.GetoptError as e:
        errorExit('%s\nSee `selfevaluation help`'%e)


if os.getuid() != 0:
    errorExit('must run as root')


if len(sys.argv) < 2:
    help()
    exit(0)

shortOptions = ''
longOptions = []

cmd = sys.argv[1]

if cmd in ('help', '-h', '--help'):
    help()
elif cmd == 'addaction':
    (opts, args) = getOptsArgs(shortOptions+'t:d:r:', longOptions)
    aid, description, rate = 1, '', 50
    date, time = str(datetime.datetime.now()).split(' ')
    time = time.split('.')[0]
    typeGiven = False
    for (key, val) in opts:
        if key == '-t':
            aType = val
            typeGiven = True
        elif key == '-d':
            description = val
        elif key == '-r':
            rate = val
    if not typeGiven:
        errorExit("Type not given.")
    t = (None, aid, 'root', description, date, time, rate)
    c.execute("INSERT INTO actions (id, action_id, username, description, date, time, rate) VALUES(?,?,?,?,?,?,?) ", t)

    
elif cmd == 'list' :
    (opts, args) = getOptsArgs(shortOptions, longOptions)
    if len(args) >1:
        errorExit("Cannot accept more than one table")
    table = args[0]
    if table == 'actions':
        c.execute("SELECT * FROM actions")
        sys.stdout.write( "id\taid\tuser\tdescription\tdate\t\ttime\trate\n")
    elif table == 'action_types':
        c.execute("SELECT * FROM action_types")
        sys.stdout.write("aid\ttitle\n")
    elif table == 'users':
        c.execute("SELECT username FROM users")
    for row in c:
        for i in row:
            try:
                sys.stdout.write(str(i)+"\t")
            except UnicodeEncodeError:
                pass
        print

elif cmd == 'adduser' :
    (opts, args) = getOptsArgs(shortOptions+"p:", longOptions)
#    if args != 1 :
 #       errorExit("Number of users given invalid.")
    username, password = args[0], ''
    for (key, val) in opts:
        if key == '-p':
            password = val

    t = (username, password)
    c.execute("INSERT INTO users (username, password) VALUES (?, ?) ", t)

conn.commit()
c.close()
