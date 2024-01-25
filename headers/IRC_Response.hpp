#ifndef IRC_RESPONSE_HPP
# define IRC_RESPONSE_HPP

enum IRC_Response
{
	NONE,
	SUCCESS,
	NICK_IN_USE,
	NOT_IN_CHANNEL,
	ALREADY_IN_CHANNEL,
	ERRONEOUS_NICK
};

#endif