#include "commands/IRC_ModeCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Errors.hpp"

#include <string>

static bool isChannel(const std::string& target)
{
	return (target[0] == '#');
}

IRC_ModeCommand::IRC_ModeCommand()
	: IRC_ACommand("MODE", 1, REGISTERED)
{}

void IRC_ModeCommand::execute(IRC_Message& message)
{
	const std::string& target = message[0];

	if (isChannel(target))
	{
		this->_executeChannel(message);
	}
	else
	{
		this->_executeUser(message);
	}
}

void IRC_ModeCommand::_executeChannel(IRC_Message& message)
{
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	IRC_Channel* targetChannel = server.findChannelByName(message[0]);
	std::string creationTime;

	if (!targetChannel)
	{
		user.reply(server, ERR_NOSUCHCHANNEL(user.getName(), message[0]));
		return ;
	}
	if (message.size() == 1) //empty modelist parameter
	{
		creationTime += targetChannel->getCreationTime();
		user.reply(server, RPL_CHANNELMODEIS(user.getName(), targetChannel->getName(), targetChannel->getModes()));
		user.reply(server, RPL_CREATIONTIME(user.getName(), targetChannel->getName(), creationTime));
		//TODO: Show the list modes of that channel
		Console::debug << "Showing the modelist of " << targetChannel->getName() << std::endl;
	}
	else //modifying chan modes
	{
	  std::vector<std::string> modes(message.getParams().begin() + 1, message.getParams().end());
		std::string response;

		response = targetChannel->setModes(modes);
		Console::debug << "Processing modelist '" << response << "' of " << targetChannel << std::endl;
	}
}

void IRC_ModeCommand::_executeUser(IRC_Message& message)
{
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	IRC_User* targetUser = server.findUserByName(message[0]);

	if (!targetUser)
	{
		user.reply(server, ERR_NOSUCHNICK(message[0]));
		return ;
	}
	if (message.size() == 2) //empty modelist parameter
	{
		//TODO: Show the list modes of that user
		Console::debug << "Showing the modelist of " << targetUser->getName() << std::endl;
	}
	else
	{
		if (targetUser == &user) //try to change modelist for own user
		{
			std::string const& modes = message[1];
			//TODO: process modelist
			Console::debug << "Processing modelist '" << modes << "' of " << targetUser << std::endl;
		}
		else
		{
			user.reply(server, ERR_USERSDONTMATH(targetUser->getName()));
		}
	}
}
