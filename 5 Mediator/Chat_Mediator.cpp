#include "Chat_Room.h"
#include "Chat_Person.h"

/*
 * Look at the notes in Chat_Room.h
 */

void test_chat_mediator()
{
    Chat_Room room;
    
    auto jordan = room.join(Chat_Person{"Jordan"});
    auto ryan = room.join(Chat_Person{"Ryan"});

    jordan->say("Hello");
    



}
