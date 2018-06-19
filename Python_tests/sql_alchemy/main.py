import sqlalchemy
print("sqlalchemy.__version__=" + sqlalchemy.__version__)

from sqlalchemy import create_engine
engine = create_engine(
        'sqlite:////home/cmss/afsm/pca/Documents/GitHub/tests/Python_tests/sql_alchemy/db.sqlite',
        echo=True
)


from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String

Base = declarative_base()

class User(Base):
    __tablename__ = 'users'

    id = sqlalchemy.Column(sqlalchemy.Integer, primary_key=True)
    name = sqlalchemy.Column(sqlalchemy.String)

    def __repr__(self):
        return "<User(name={})>".format(self.name)

Base.metadata.create_all(engine)


from sqlalchemy.orm import sessionmaker
SessionClass = sessionmaker(bind=engine)


session_instance = SessionClass()

session_instance.add(User(name='Phil'))
session_instance.commit()

""" REF https://docs.sqlalchemy.org/en/latest/orm/tutorial.html """




