#pragma once

//
// this defines part of the consequences of the collisions
// consists of three types of ids
//    the unique id, which is unique to every object
//    the group id, which shows in which group the object in (for example a ship and its bullets)
//    the team id, which is the team of the object
//    group and team id both have an extremal value to show it doesn't belong into any group or team
//
class Identifier
{
public:
  typedef int UniqueIdType;
  typedef int GroupIdType;
  typedef int TeamIdType;

  UniqueIdType& uniqueId()
  {
    return m_uniqueId;
  }

  GroupIdType& groupId()
  {
    return m_groupId;
  }

  TeamIdType& teamId()
  {
    return m_teamId;
  }

private:
  UniqueIdType  m_uniqueId;
  GroupIdType   m_groupId;
  TeamIdType    m_teamId;
};

