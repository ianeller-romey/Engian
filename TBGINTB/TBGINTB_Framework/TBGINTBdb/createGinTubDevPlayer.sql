USE [GinTub]

DECLARE @devUserName varchar(max)
DECLARE @devDomainName varchar(max)
DECLARE @devDomain varchar(max)
DECLARE @devPassword varchar(max)
SET @devUserName = 'dev'
SET @devDomainName = 'ironandrose'
SET @devDomain = 'com'
SET @devPassword = 'gintub'

INSERT INTO [dbo].[EmailUserNames] ([UserName])
VALUES (@devUserName)
DECLARE @devUserNameId int
SELECT @devUserNameId = SCOPE_IDENTITY()

INSERT INTO [dbo].[EmailDomainNames] ([DomainName])
VALUES (@devDomainName)
DECLARE @devDomainNameId int
SELECT @devDomainNameId = SCOPE_IDENTITY()

INSERT INTO [dbo].[EmailDomains] ([Domain])
VALUES (@devDomain)
DECLARE @devDomainId int
SELECT @devDomainId = SCOPE_IDENTITY()	

DECLARE @devPlayerId uniqueidentifier
SELECT @devPlayerId = 'E1751135-88F7-46D4-9D78-FA3769A571AB'

INSERT INTO [dbo].[Players] ([EmailUserName], [EmailDomainName], [EmailDomain], [Password], [Id], [LastCheckpoint])
VALUES (@devUserNameId, @devDomainNameId, @devDomainId, @devPassword, @devPlayerId, GETDATE())

IF NOT EXISTS (SELECT 1 FROM [dbo].[PlayerStatesOfRooms] WHERE [Player] = @devPlayerId)
AND NOT EXISTS (SELECT 1 FROM [dbo].[PlayerStatesOfParagraphs] WHERE [Player] = @devPlayerId)
	EXEC [dbo].[dbo_LoadDefaultPlayerStates] @playerId = @devPlayerId