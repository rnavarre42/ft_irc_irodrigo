/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_User.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:05:44 by irodrigo          #+#    #+#             */
/*   Updated: 2023/12/19 10:14:59 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_USER_HPP
# define IRC_USER_HPP

# include "IRC_Channel.hpp"
# include "IRC_Message.hpp"

# include <set>
# include <vector>
# include <string>
# include <ctime>

struct IRC_Server;

struct IRC_User
{
	typedef std::vector<IRC_Channel*>		channelsVectorType;
	typedef std::set<IRC_Channel*>			channelsSetType;
	typedef channelsSetType::iterator		channelsSetIterator;
	typedef channelsSetType::const_iterator	channelsSetConstIterator;

	IRC_User(struct pollfd* pollPosition);
	IRC_User(struct pollfd* pollPosition, const std::string& nick, const std::string& ident, const std::string& realname);
	~IRC_User();

	bool isInChannel(IRC_Channel*);
	bool addChannel(IRC_Channel*);
	bool removeChannel(IRC_Channel*);

	void addReceiveData(char* buffer);

	const channelsSetType		getChannels() const;
	IRC_Channel::usersSetType*	getCommonUsersExcept(IRC_User*);
	IRC_Channel::usersSetType*	getCommonUsers();

	int getFd() const;
	int	getAccess() const;
	struct pollfd*		getPollPosition();
	const std::string&	getName() const;
	const std::string		getMask() const;
	const std::string&  getHost() const;
	//const std::string	getUsers() const;  // habrá que crearlas
	const std::string&	getIdent() const;
	const std::string&	getRealName() const;
	const std::string&	getPass() const;
	time_t				getUserTimeOut();


	void setFd(int);
	void setName(const std::string& value);
	void setUserTimeout(time_t myTimeOut);
	void setIdent(const std::string& value);
	void setRealName(const std::string& value);
	void setHost(const std::string& value);
	void setAccess(int access);
	void setPass(const std::string& value);

	void send(const std::string& data);
	void reply(const IRC_User* user, const std::string& data);
	void reply(const IRC_Server* server, const std::string& data);

	void markForDelete();
	bool deleteMarked() const;
//	void	errorReply(const std::string& reply);
	//void	send(IRC_Message& message);

private:
	struct pollfd*		_pollPosition;
	std::string			_name;
	std::string			_ident;
	std::string			_realname;
	std::string			_hostname;
	std::string			_pass;
	int					_access;
	channelsSetType		_channels;
	std::string			_inputBuffer;
	std::string			_outputBuffer;
	time_t				_registratedT;				// moment that user has registered in server
	time_t				_timeout;					// calculate timeout
	time_t				_time;						// check last command time
	bool					_deleteMarked;
	
	IRC_User(const IRC_User&);
	IRC_User& operator=(const IRC_User&);

	void 	_resetTime(void);
	time_t 	_getTime(void);
	time_t	_getRegTime(void);

	friend struct IRC_Server;
};

#endif
