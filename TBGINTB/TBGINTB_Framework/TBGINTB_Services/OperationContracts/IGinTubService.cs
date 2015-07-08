using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

using GinTub.Services;


namespace GinTub.Services.OperationContracts
{
    [ServiceContract]
    public interface IGinTubService
    {
        [OperationContract]
        [WebInvoke(Method = "POST",
        BodyStyle = WebMessageBodyStyle.Wrapped,
        RequestFormat = WebMessageFormat.Json,
        ResponseFormat = WebMessageFormat.Json,
        UriTemplate = "PlayerLogin")]
        DataContracts.PlayerLogin PlayerLogin(string emailAddress, string password);

        [OperationContract]
        [WebInvoke(Method = "GET",
        BodyStyle = WebMessageBodyStyle.Wrapped,
        RequestFormat = WebMessageFormat.Json,
        ResponseFormat = WebMessageFormat.Json,
        UriTemplate = "LoadAllVerbTypes")]
        DataContracts.VerbUseData LoadAllVerbTypes();

        [OperationContract]
        [WebInvoke(Method = "POST",
        BodyStyle = WebMessageBodyStyle.Wrapped,
        RequestFormat = WebMessageFormat.Json,
        ResponseFormat = WebMessageFormat.Json,
        UriTemplate = "LoadNounsForParagraphState")]
        DataContracts.MessageData LoadNounsForParagraphState(int paragraphStateId);

        [OperationContract]
        [WebInvoke(Method = "POST",
        BodyStyle = WebMessageBodyStyle.Wrapped,
        RequestFormat = WebMessageFormat.Json,
        ResponseFormat = WebMessageFormat.Json,
        UriTemplate = "LoadGame")]
        DataContracts.PlayData LoadGame(Guid playerId);
    }
}
