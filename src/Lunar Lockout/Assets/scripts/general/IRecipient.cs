using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public interface IRecipient
{
    void Receive(IMessage message);
}