USE [GinTub]

DECLARE @devUserName varchar(max)
DECLARE @devDomainName varchar(max)
DECLARE @devDomain varchar(max)
DECLARE @devPassword varchar(max)
SET @devUserName = 'dev'
SET @devDomainName = 'ironandrose'
SET @devDomain = 'com'
SET @devPassword = 'gintub'

IF NOT EXISTS (SELECT 1 FROM [dbo].[EmailUserNames] WHERE [UserName] = @devUserName)
	INSERT INTO [dbo].[EmailUserNames] ([UserName])
	VALUES (@devUserName)
DECLARE @devUserNameId int
SELECT @devUserNameId = [Id] FROM [dbo].[EmailUserNames] WHERE [UserName] = @devUserName

IF NOT EXISTS (SELECT 1 FROM [dbo].[EmailDomainNames] WHERE [DomainName] = @devDomainName)
	INSERT INTO [dbo].[EmailDomainNames] ([DomainName])
	VALUES (@devDomainName)
DECLARE @devDomainNameId int
SELECT @devDomainNameId = [Id] FROM [dbo].[EmailDomainNames] WHERE [DomainName] = @devDomainName

IF NOT EXISTS (SELECT 1 FROM [dbo].[EmailDomains] WHERE [Domain] = @devDomain)
	INSERT INTO [dbo].[EmailDomains] ([Domain])
	VALUES (@devDomain)
DECLARE @devDomainId int
SELECT @devDomainId = [Id] FROM [dbo].[EmailDomains] WHERE [Domain] = @devDomain

DECLARE @devPlayerId uniqueidentifier
SET @devPlayerId = 'E1751135-88F7-46D4-9D78-FA3769A571AB'

IF NOT EXISTS (SELECT 1 FROM [dbo].[Players] WHERE [Id] = @devPlayerId)
	INSERT INTO [dbo].[Players] ([EmailUserName], [EmailDomainName], [EmailDomain], [Password], [Id], [LastCheckpoint], [LastRoom])
	SELECT
		@devUserNameId, 
		@devDomainNameId, 
		@devDomainId, 
		@devPassword, 
		@devPlayerId, 
		GETDATE(),
		[Room]
	FROM [dbo].[AreaRoomOnInitialLoad]

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