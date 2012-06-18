#ifndef _IDENTIFIER_H_
#define _IDENTIFIER_H_

//
// class that represents the general identifier of all flying things
//

class Identifier
{
  public:
    typedef int UniqueId;
    typedef int PersonalId;
    typedef int TeamId;

    Identifier(UniqueId uid, PersonalId pid, TeamId tid): m_uid(uid), m_pid(pid), m_tid(tid)
    { }
    UniqueId GetUniqueId() const
    {
      return m_uid;
    }
    PersonalId GetPersonalId() const
    {
      return m_pid;
    }
    TeamId GetTeamId() const
    {
      return m_tid;
    }
  private:
    UniqueId    m_uid;
    PersonalId  m_pid;
    TeamId      m_tid;
};

#endif
