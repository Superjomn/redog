'''
Created on Jan 3, 2013

@author: chunwei
'''
from sqlalchemy import Table, create_engine, ForeignKey
from sqlalchemy import Column, Date, Integer, String, Boolean, Float
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship, backref
Base = declarative_base()

class User(Base):
    __tablename__ = 'user'
    id = Column(Integer, primary_key=True)
    userID = Column(Integer)
    # one to many
    movies = relationship("Movie")
    def __init__(self, id):
        self.userID = id

class Movie(Base):
    __tablename__ = 'movie'
    id = Column(Integer, primary_key=True)
    itemID = Column(Integer)
    rank = Column(Integer)
    user_id = Column(Integer, ForeignKey('user.id'))
    def __init__(self, id, rank):
        self.itemID = id
        self.rank = rank
    
    
# create tables
if __name__ == '__main__' :
    engine = create_engine('sqlite:////home/chunwei/NetFlixData/training_set.db', echo=True)
    Base.metadata.create_all(engine)
    print 'db ok!'
