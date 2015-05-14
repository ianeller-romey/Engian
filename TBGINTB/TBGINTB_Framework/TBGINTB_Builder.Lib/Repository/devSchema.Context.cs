﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated from a template.
//
//     Manual changes to this file may cause unexpected behavior in your application.
//     Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace TBGINTB_Builder.Lib.Repository
{
    using System;
    using System.Data.Entity;
    using System.Data.Entity.Infrastructure;
    using System.Data.Entity.Core.Objects;
    using System.Linq;
    
    public partial class GinTubEntities : DbContext
    {
        public GinTubEntities()
            : base("name=GinTubEntities")
        {
        }
    
        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            throw new UnintentionalCodeFirstException();
        }
    
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddAction(Nullable<int> noun, Nullable<int> verbtype)
        {
            var nounParameter = noun.HasValue ?
                new ObjectParameter("noun", noun) :
                new ObjectParameter("noun", typeof(int));
    
            var verbtypeParameter = verbtype.HasValue ?
                new ObjectParameter("verbtype", verbtype) :
                new ObjectParameter("verbtype", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddAction", nounParameter, verbtypeParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddArea(string name)
        {
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddArea", nameParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddCharacter(string name, string description)
        {
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            var descriptionParameter = description != null ?
                new ObjectParameter("description", description) :
                new ObjectParameter("description", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddCharacter", nameParameter, descriptionParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddEvent(string name, string description)
        {
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            var descriptionParameter = description != null ?
                new ObjectParameter("description", description) :
                new ObjectParameter("description", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddEvent", nameParameter, descriptionParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddItem(string name, string description)
        {
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            var descriptionParameter = description != null ?
                new ObjectParameter("description", description) :
                new ObjectParameter("description", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddItem", nameParameter, descriptionParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddLocation(string location)
        {
            var locationParameter = location != null ?
                new ObjectParameter("location", location) :
                new ObjectParameter("location", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddLocation", locationParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddMessage(string text)
        {
            var textParameter = text != null ?
                new ObjectParameter("text", text) :
                new ObjectParameter("text", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddMessage", textParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddMessageChoice(Nullable<int> message, string text)
        {
            var messageParameter = message.HasValue ?
                new ObjectParameter("message", message) :
                new ObjectParameter("message", typeof(int));
    
            var textParameter = text != null ?
                new ObjectParameter("text", text) :
                new ObjectParameter("text", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddMessageChoice", messageParameter, textParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddMessageChoiceOutcome(Nullable<int> messagechoice, Nullable<int> result)
        {
            var messagechoiceParameter = messagechoice.HasValue ?
                new ObjectParameter("messagechoice", messagechoice) :
                new ObjectParameter("messagechoice", typeof(int));
    
            var resultParameter = result.HasValue ?
                new ObjectParameter("result", result) :
                new ObjectParameter("result", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddMessageChoiceOutcome", messagechoiceParameter, resultParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddNoun(string text, Nullable<int> paragraph, Nullable<int> paragraphstate)
        {
            var textParameter = text != null ?
                new ObjectParameter("text", text) :
                new ObjectParameter("text", typeof(string));
    
            var paragraphParameter = paragraph.HasValue ?
                new ObjectParameter("paragraph", paragraph) :
                new ObjectParameter("paragraph", typeof(int));
    
            var paragraphstateParameter = paragraphstate.HasValue ?
                new ObjectParameter("paragraphstate", paragraphstate) :
                new ObjectParameter("paragraphstate", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddNoun", textParameter, paragraphParameter, paragraphstateParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddParagraph(string text, Nullable<int> room, Nullable<int> roomstate)
        {
            var textParameter = text != null ?
                new ObjectParameter("text", text) :
                new ObjectParameter("text", typeof(string));
    
            var roomParameter = room.HasValue ?
                new ObjectParameter("room", room) :
                new ObjectParameter("room", typeof(int));
    
            var roomstateParameter = roomstate.HasValue ?
                new ObjectParameter("roomstate", roomstate) :
                new ObjectParameter("roomstate", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddParagraph", textParameter, roomParameter, roomstateParameter);
        }
    
        public virtual int dev_AddPlayer(string username, string domainname, string domain, string password)
        {
            var usernameParameter = username != null ?
                new ObjectParameter("username", username) :
                new ObjectParameter("username", typeof(string));
    
            var domainnameParameter = domainname != null ?
                new ObjectParameter("domainname", domainname) :
                new ObjectParameter("domainname", typeof(string));
    
            var domainParameter = domain != null ?
                new ObjectParameter("domain", domain) :
                new ObjectParameter("domain", typeof(string));
    
            var passwordParameter = password != null ?
                new ObjectParameter("password", password) :
                new ObjectParameter("password", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_AddPlayer", usernameParameter, domainnameParameter, domainParameter, passwordParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddPlayerHistory(Nullable<System.Guid> player, Nullable<int> @event)
        {
            var playerParameter = player.HasValue ?
                new ObjectParameter("player", player) :
                new ObjectParameter("player", typeof(System.Guid));
    
            var eventParameter = @event.HasValue ?
                new ObjectParameter("event", @event) :
                new ObjectParameter("event", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddPlayerHistory", playerParameter, eventParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddPlayerInventory(Nullable<System.Guid> player, Nullable<int> item, Nullable<bool> active)
        {
            var playerParameter = player.HasValue ?
                new ObjectParameter("player", player) :
                new ObjectParameter("player", typeof(System.Guid));
    
            var itemParameter = item.HasValue ?
                new ObjectParameter("item", item) :
                new ObjectParameter("item", typeof(int));
    
            var activeParameter = active.HasValue ?
                new ObjectParameter("active", active) :
                new ObjectParameter("active", typeof(bool));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddPlayerInventory", playerParameter, itemParameter, activeParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddPlayerParty(Nullable<System.Guid> player, Nullable<int> character, Nullable<bool> active)
        {
            var playerParameter = player.HasValue ?
                new ObjectParameter("player", player) :
                new ObjectParameter("player", typeof(System.Guid));
    
            var characterParameter = character.HasValue ?
                new ObjectParameter("Character", character) :
                new ObjectParameter("Character", typeof(int));
    
            var activeParameter = active.HasValue ?
                new ObjectParameter("active", active) :
                new ObjectParameter("active", typeof(bool));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddPlayerParty", playerParameter, characterParameter, activeParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddRequirement(Nullable<int> action, Nullable<int> requirementsourcetype, Nullable<int> requirement)
        {
            var actionParameter = action.HasValue ?
                new ObjectParameter("action", action) :
                new ObjectParameter("action", typeof(int));
    
            var requirementsourcetypeParameter = requirementsourcetype.HasValue ?
                new ObjectParameter("requirementsourcetype", requirementsourcetype) :
                new ObjectParameter("requirementsourcetype", typeof(int));
    
            var requirementParameter = requirement.HasValue ?
                new ObjectParameter("requirement", requirement) :
                new ObjectParameter("requirement", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddRequirement", actionParameter, requirementsourcetypeParameter, requirementParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddRequirementSourceType(string name)
        {
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddRequirementSourceType", nameParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddResult(Nullable<int> resulttype, Nullable<int> resultsourcetype, Nullable<int> source, string jsondata)
        {
            var resulttypeParameter = resulttype.HasValue ?
                new ObjectParameter("resulttype", resulttype) :
                new ObjectParameter("resulttype", typeof(int));
    
            var resultsourcetypeParameter = resultsourcetype.HasValue ?
                new ObjectParameter("resultsourcetype", resultsourcetype) :
                new ObjectParameter("resultsourcetype", typeof(int));
    
            var sourceParameter = source.HasValue ?
                new ObjectParameter("source", source) :
                new ObjectParameter("source", typeof(int));
    
            var jsondataParameter = jsondata != null ?
                new ObjectParameter("jsondata", jsondata) :
                new ObjectParameter("jsondata", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddResult", resulttypeParameter, resultsourcetypeParameter, sourceParameter, jsondataParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddResultSourceType(string name)
        {
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddResultSourceType", nameParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddResultType(string name)
        {
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddResultType", nameParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddRoom(string name, Nullable<int> x, Nullable<int> y, Nullable<int> z, Nullable<int> area)
        {
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            var xParameter = x.HasValue ?
                new ObjectParameter("x", x) :
                new ObjectParameter("x", typeof(int));
    
            var yParameter = y.HasValue ?
                new ObjectParameter("y", y) :
                new ObjectParameter("y", typeof(int));
    
            var zParameter = z.HasValue ?
                new ObjectParameter("z", z) :
                new ObjectParameter("z", typeof(int));
    
            var areaParameter = area.HasValue ?
                new ObjectParameter("area", area) :
                new ObjectParameter("area", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddRoom", nameParameter, xParameter, yParameter, zParameter, areaParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddRoomState(Nullable<int> room, Nullable<int> state, Nullable<int> location, Nullable<System.DateTime> time)
        {
            var roomParameter = room.HasValue ?
                new ObjectParameter("room", room) :
                new ObjectParameter("room", typeof(int));
    
            var stateParameter = state.HasValue ?
                new ObjectParameter("state", state) :
                new ObjectParameter("state", typeof(int));
    
            var locationParameter = location.HasValue ?
                new ObjectParameter("location", location) :
                new ObjectParameter("location", typeof(int));
    
            var timeParameter = time.HasValue ?
                new ObjectParameter("time", time) :
                new ObjectParameter("time", typeof(System.DateTime));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddRoomState", roomParameter, stateParameter, locationParameter, timeParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddVerb(string name, Nullable<int> verbtype)
        {
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            var verbtypeParameter = verbtype.HasValue ?
                new ObjectParameter("verbtype", verbtype) :
                new ObjectParameter("verbtype", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddVerb", nameParameter, verbtypeParameter);
        }
    
        public virtual ObjectResult<Nullable<decimal>> dev_AddVerbType(string name)
        {
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<Nullable<decimal>>("dev_AddVerbType", nameParameter);
        }
    
        public virtual int dev_ShiftRoom(Nullable<int> id, Nullable<int> xIncr, Nullable<int> yIncr, Nullable<int> zIncr)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var xIncrParameter = xIncr.HasValue ?
                new ObjectParameter("xIncr", xIncr) :
                new ObjectParameter("xIncr", typeof(int));
    
            var yIncrParameter = yIncr.HasValue ?
                new ObjectParameter("yIncr", yIncr) :
                new ObjectParameter("yIncr", typeof(int));
    
            var zIncrParameter = zIncr.HasValue ?
                new ObjectParameter("zIncr", zIncr) :
                new ObjectParameter("zIncr", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_ShiftRoom", idParameter, xIncrParameter, yIncrParameter, zIncrParameter);
        }
    
        public virtual int dev_UpdateAction(Nullable<int> id, Nullable<int> noun, Nullable<int> verbtype)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var nounParameter = noun.HasValue ?
                new ObjectParameter("noun", noun) :
                new ObjectParameter("noun", typeof(int));
    
            var verbtypeParameter = verbtype.HasValue ?
                new ObjectParameter("verbtype", verbtype) :
                new ObjectParameter("verbtype", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateAction", idParameter, nounParameter, verbtypeParameter);
        }
    
        public virtual int dev_UpdateArea(Nullable<int> id, string name)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateArea", idParameter, nameParameter);
        }
    
        public virtual int dev_UpdateCharacter(Nullable<int> id, string name, string description)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            var descriptionParameter = description != null ?
                new ObjectParameter("description", description) :
                new ObjectParameter("description", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateCharacter", idParameter, nameParameter, descriptionParameter);
        }
    
        public virtual int dev_UpdateEvent(Nullable<int> id, string name, string description)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            var descriptionParameter = description != null ?
                new ObjectParameter("description", description) :
                new ObjectParameter("description", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateEvent", idParameter, nameParameter, descriptionParameter);
        }
    
        public virtual int dev_UpdateItem(Nullable<int> id, string name, string description)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            var descriptionParameter = description != null ?
                new ObjectParameter("description", description) :
                new ObjectParameter("description", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateItem", idParameter, nameParameter, descriptionParameter);
        }
    
        public virtual int dev_UpdateLocation(Nullable<int> id, string location)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var locationParameter = location != null ?
                new ObjectParameter("location", location) :
                new ObjectParameter("location", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateLocation", idParameter, locationParameter);
        }
    
        public virtual int dev_UpdateMessage(Nullable<int> id, string text)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var textParameter = text != null ?
                new ObjectParameter("text", text) :
                new ObjectParameter("text", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateMessage", idParameter, textParameter);
        }
    
        public virtual int dev_UpdateMessageChoice(Nullable<int> id, string text)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var textParameter = text != null ?
                new ObjectParameter("text", text) :
                new ObjectParameter("text", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateMessageChoice", idParameter, textParameter);
        }
    
        public virtual int dev_UpdateMessageChoiceOutcome(Nullable<int> id, Nullable<int> result)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var resultParameter = result.HasValue ?
                new ObjectParameter("result", result) :
                new ObjectParameter("result", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateMessageChoiceOutcome", idParameter, resultParameter);
        }
    
        public virtual int dev_UpdateParagraph(Nullable<int> id, string text, Nullable<int> room, Nullable<int> roomstate, Nullable<int> state)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var textParameter = text != null ?
                new ObjectParameter("text", text) :
                new ObjectParameter("text", typeof(string));
    
            var roomParameter = room.HasValue ?
                new ObjectParameter("room", room) :
                new ObjectParameter("room", typeof(int));
    
            var roomstateParameter = roomstate.HasValue ?
                new ObjectParameter("roomstate", roomstate) :
                new ObjectParameter("roomstate", typeof(int));
    
            var stateParameter = state.HasValue ?
                new ObjectParameter("state", state) :
                new ObjectParameter("state", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateParagraph", idParameter, textParameter, roomParameter, roomstateParameter, stateParameter);
        }
    
        public virtual int dev_UpdatePlayerInventory(Nullable<System.Guid> player, Nullable<int> item, Nullable<bool> active)
        {
            var playerParameter = player.HasValue ?
                new ObjectParameter("player", player) :
                new ObjectParameter("player", typeof(System.Guid));
    
            var itemParameter = item.HasValue ?
                new ObjectParameter("item", item) :
                new ObjectParameter("item", typeof(int));
    
            var activeParameter = active.HasValue ?
                new ObjectParameter("active", active) :
                new ObjectParameter("active", typeof(bool));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdatePlayerInventory", playerParameter, itemParameter, activeParameter);
        }
    
        public virtual int dev_UpdatePlayerParty(Nullable<System.Guid> player, Nullable<int> character, Nullable<bool> active)
        {
            var playerParameter = player.HasValue ?
                new ObjectParameter("player", player) :
                new ObjectParameter("player", typeof(System.Guid));
    
            var characterParameter = character.HasValue ?
                new ObjectParameter("Character", character) :
                new ObjectParameter("Character", typeof(int));
    
            var activeParameter = active.HasValue ?
                new ObjectParameter("active", active) :
                new ObjectParameter("active", typeof(bool));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdatePlayerParty", playerParameter, characterParameter, activeParameter);
        }
    
        public virtual int dev_UpdateRequirement(Nullable<int> id, Nullable<int> action, Nullable<int> requirementsourcetype, Nullable<int> requirement)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var actionParameter = action.HasValue ?
                new ObjectParameter("action", action) :
                new ObjectParameter("action", typeof(int));
    
            var requirementsourcetypeParameter = requirementsourcetype.HasValue ?
                new ObjectParameter("requirementsourcetype", requirementsourcetype) :
                new ObjectParameter("requirementsourcetype", typeof(int));
    
            var requirementParameter = requirement.HasValue ?
                new ObjectParameter("requirement", requirement) :
                new ObjectParameter("requirement", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateRequirement", idParameter, actionParameter, requirementsourcetypeParameter, requirementParameter);
        }
    
        public virtual int dev_UpdateRequirementSourceType(Nullable<int> id, string name)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateRequirementSourceType", idParameter, nameParameter);
        }
    
        public virtual int dev_UpdateResult(Nullable<int> id, Nullable<int> resulttype, Nullable<int> resultsourcetype, Nullable<int> source, string jsondata)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var resulttypeParameter = resulttype.HasValue ?
                new ObjectParameter("resulttype", resulttype) :
                new ObjectParameter("resulttype", typeof(int));
    
            var resultsourcetypeParameter = resultsourcetype.HasValue ?
                new ObjectParameter("resultsourcetype", resultsourcetype) :
                new ObjectParameter("resultsourcetype", typeof(int));
    
            var sourceParameter = source.HasValue ?
                new ObjectParameter("source", source) :
                new ObjectParameter("source", typeof(int));
    
            var jsondataParameter = jsondata != null ?
                new ObjectParameter("jsondata", jsondata) :
                new ObjectParameter("jsondata", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateResult", idParameter, resulttypeParameter, resultsourcetypeParameter, sourceParameter, jsondataParameter);
        }
    
        public virtual int dev_UpdateResultSourceType(Nullable<int> id, string name)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateResultSourceType", idParameter, nameParameter);
        }
    
        public virtual int dev_UpdateResultType(Nullable<int> id, string name)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateResultType", idParameter, nameParameter);
        }
    
        public virtual int dev_UpdateRoom(Nullable<int> id, string name, Nullable<int> x, Nullable<int> y, Nullable<int> z, Nullable<int> area)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            var xParameter = x.HasValue ?
                new ObjectParameter("x", x) :
                new ObjectParameter("x", typeof(int));
    
            var yParameter = y.HasValue ?
                new ObjectParameter("y", y) :
                new ObjectParameter("y", typeof(int));
    
            var zParameter = z.HasValue ?
                new ObjectParameter("z", z) :
                new ObjectParameter("z", typeof(int));
    
            var areaParameter = area.HasValue ?
                new ObjectParameter("area", area) :
                new ObjectParameter("area", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateRoom", idParameter, nameParameter, xParameter, yParameter, zParameter, areaParameter);
        }
    
        public virtual int dev_UpdateRoomState(Nullable<int> id, Nullable<int> room, Nullable<int> state, Nullable<int> location, Nullable<System.DateTime> time)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var roomParameter = room.HasValue ?
                new ObjectParameter("room", room) :
                new ObjectParameter("room", typeof(int));
    
            var stateParameter = state.HasValue ?
                new ObjectParameter("state", state) :
                new ObjectParameter("state", typeof(int));
    
            var locationParameter = location.HasValue ?
                new ObjectParameter("location", location) :
                new ObjectParameter("location", typeof(int));
    
            var timeParameter = time.HasValue ?
                new ObjectParameter("time", time) :
                new ObjectParameter("time", typeof(System.DateTime));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateRoomState", idParameter, roomParameter, stateParameter, locationParameter, timeParameter);
        }
    
        public virtual int dev_UpdateVerb(Nullable<int> id, string name, Nullable<int> verbtype)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            var verbtypeParameter = verbtype.HasValue ?
                new ObjectParameter("verbtype", verbtype) :
                new ObjectParameter("verbtype", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateVerb", idParameter, nameParameter, verbtypeParameter);
        }
    
        public virtual int dev_UpdateVerbType(Nullable<int> id, string name)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            var nameParameter = name != null ?
                new ObjectParameter("name", name) :
                new ObjectParameter("name", typeof(string));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("dev_UpdateVerbType", idParameter, nameParameter);
        }
    
        public virtual ObjectResult<dev_GetAllAreas_Result> dev_GetAllAreas()
        {
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<dev_GetAllAreas_Result>("dev_GetAllAreas");
        }
    
        public virtual ObjectResult<dev_GetAllRoomsInArea_Result> dev_GetAllRoomsInArea(Nullable<int> area)
        {
            var areaParameter = area.HasValue ?
                new ObjectParameter("area", area) :
                new ObjectParameter("area", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<dev_GetAllRoomsInArea_Result>("dev_GetAllRoomsInArea", areaParameter);
        }
    
        public virtual ObjectResult<dev_GetArea_Result> dev_GetArea(Nullable<int> id)
        {
            var idParameter = id.HasValue ?
                new ObjectParameter("id", id) :
                new ObjectParameter("id", typeof(int));
    
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction<dev_GetArea_Result>("dev_GetArea", idParameter);
        }
    }
}
