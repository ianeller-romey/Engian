USE [GinTub]

DECLARE @devUserName varchar(max)
DECLARE @devDomainName varchar(max)
DECLARE @devDomain varchar(max)
DECLARE @devPassword varchar(max)
SET @devUserName = 'dev'
SET @devDomainName = 'ironandrose'
SET @devDomain = 'com'
SET @devPassword = 'gintub'

DECLARE @devPlayerId uniqueidentifier
SET @devPlayerId = 'E1751135-88F7-46D4-9D78-FA3769A571AB'

IF NOT EXISTS (SELECT 1 FROM [dbo].[Players] WHERE [Id] = @devPlayerId)
	EXEC [dev].[dev_AddPlayer]
	@username = @devUserName,
	@domainname = @devDomainName,
	@domain = @devDomain,
	@password = @devPassword,
	@playerid = @devPlayerId

IF NOT EXISTS (SELECT 1 FROM [dev].[DevPlayers] WHERE [Player] = @devPlayerId)
	INSERT INTO [dev].[DevPlayers] ([Player])
	VALUES (@devPlayerId)

IF NOT EXISTS (SELECT 1 FROM [dbo].[PlayerStatesOfRooms] WHERE [Player] = @devPlayerId)
AND NOT EXISTS (SELECT 1 FROM [dbo].[PlayerStatesOfParagraphs] WHERE [Player] = @devPlayerId)
	EXEC [dbo].[CreateDefaultPlayerStates] @player = @devPlayerId

IF NOT EXISTS (SELECT 1 FROM [dbo].[PlayerInventory] WHERE [Player] = @devPlayerId)
AND NOT EXISTS (SELECT 1 FROM [dbo].[PlayerHistory] WHERE [Player] = @devPlayerId)
AND NOT EXISTS (SELECT 1 FROM [dbo].[PlayerParty] WHERE [Player] = @devPlayerId)
	EXEC [dbo].[CreateDefaultPlayerInventories] @player = @devPlayerId