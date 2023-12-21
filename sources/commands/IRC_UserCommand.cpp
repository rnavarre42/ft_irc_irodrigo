# include "commands/IRC_UserCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Errors.hpp"

# include <iostream>

IRC_UserCommand::IRC_UserCommand()
    : IRC_ACommand("USER", 4, 0)
{}

void IRC_UserCommand::execute(IRC_Message& message)
{
		IRC_User& user = message.getUser();
		IRC_Server& server = message.getServer();

    if (user.getAccess() > 0)
    {
        user.send(ERR_ALREADYREGISTRED);
        return ;
    }  
    user.setIdent(message[0]);
    user.setRealName(message[3]);
    if (server.setRegisteredUser(user))
    {
				//TODO: Check password?
        server.sendMOTDMsg(&user);
    }

        //ToDo: ¿aquí hay que mirar más cosas ...... Envío del ping y más ....?
		/*
    std::cout << "nick usuario = " << user.getName() << std::endl;
    std::cout << "| ident usuario = " << user.getIdent();
    std::cout << "| fd usuario = " << user.getFd();
    std::cout << " desde IRC_UserCommand" << std::endl;
    */
}
