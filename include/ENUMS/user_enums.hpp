#ifndef __USER_ENUMS_H__
#define __USER_ENUMS_H__

enum infoState
{
    INFO_STATE_SUCCESSFUL,
    INFO_STATE_FAILED
};

enum rolesTypes
{
    ADMIN,
    BOOKING_AGENT,
    PASSENGER
};

enum userState
{
    USER_VIEWED,
    ADDED_USER,
    UPDATED_USER,
    DELETED_USER,
    FAILED_OPERATION
};

enum logState
{
    LOG_STATE_SUCCESSFUL,
    LOG_STATE_FAILED
};

#endif // __USER_ENUMS_H__