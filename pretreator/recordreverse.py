'''
Created on Jan 3, 2013

@author: chunwei
'''
import os
from sqlalchemy import  create_engine
from sqlalchemy.orm import sessionmaker
import table_def as db
import common

class RecordReverse:
    def __init__(self, dir='/home/chunwei/NetFlixData/training_set/', dbpath='sqlite:////home/chunwei/NetFlixData/training_set.db'):
        self._dir = dir
        self._dbpath = dbpath
        self.datadic = {}
    
    def setup(self):
        engine = create_engine(self._dbpath, echo=False)
        # create a Session
        Session = sessionmaker(bind=engine)
        self.session = Session()  

    def load(self):
        files = os.listdir(self._dir)
        for f in files:
            path = os.path.join(self._dir, f)
            f = open(path)
            content = f.read()
            yield content
            f.close()

    def parse(self):
        for i,c in enumerate(self.load()):
            #self.output_all(i+1)
            print 'parse %d th file' % i
            if i % 100: print '.. has parsed %d files' % i
            movie = 0
            lines = c.split('\n')
            for l in lines:
                if len(l.split(',')) < 3 and common.canfind(l, ':'):
                    '''
                    movie id
                    '''
                    words = l.split(':')
                    movie = int(words[0])
                    assert movie<17779, 'Error: movieid greater than max 17770'
                else:
                    #get user record
                    #parse line
                    words = l.split(',')
                    try:
                        userid = int(words[0])
                        rank = int(words[1])
                    except:
                        continue
                    assert userid < 2649440, 'Error: userid greater than max'
                    assert rank <= 5, 'Error: rank greater than max 5'
                    #add record to dic
                    if not self.datadic.has_key(userid):
                        #create new key
                        self.datadic[userid] = []
                    self.datadic[userid].append((movie, rank))
        #last turn ,just output remains
        #self.output_all(-1)
    
    def output_all(self, i):
        print 'i: ', i
        print 'dic: ', self.datadic
        if i == -1 or i % 500 == 0:
            '''
            final turn, just output all
            or files one turn
            '''
            print '.. write to db'
            for r in self.datadic.items():
                self.output(r[0], r[1])
            #refresh empty
            self.datadic = {}
            
            
    def output(self, userid, records):
        '''
        records = [(userid, recor)]
        '''
        print '.. outputing ..', userid
        #find if thereis userrecord
        user = self.session.query(db.User).filter(db.User.userID == userid).first()
        if not user:
            #add user
            user = db.User(userid)
        #add records
        for r in records:
            record = db.Movie(r[0], r[1])
            user.movies.append(record)
            self.session.add(record)
        self.session.add(user)
        self.session.commit()

if __name__ == '__main__':
    r = RecordReverse()
    r.setup()
    r.parse()
