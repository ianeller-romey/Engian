USE [GinTub]

CREATE TABLE [dbo].[Areas] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL
)

CREATE TABLE [dbo].[Locations] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[LocationFile] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[Rooms] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[X] int NOT NULL,
	[Y] int NOT NULL,
	[Z] int NOT NULL,
	[Area] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Areas]([Id])
)

CREATE TABLE [dbo].[RoomStates] (
	[Id] int PRIMARY KEY IDENTITY,
	[State] int NOT NULL,
	[Time] datetime NULL,
	[Location] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Locations]([Id]),
	[Room] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id])
)

CREATE TABLE [dbo].[Paragraphs] (
	[Id] int PRIMARY KEY IDENTITY,
	[Order] int NOT NULL,
	[Room] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id]),
	[RoomState] int NULL FOREIGN KEY REFERENCES [dbo].[RoomStates]([Id]),
	CONSTRAINT UQ__ParagraphsOrder UNIQUE NONCLUSTERED ([Order], [Room], [RoomState])
)

CREATE TABLE [dbo].[ParagraphStates] (
	[Id] int PRIMARY KEY IDENTITY,
	[Text] varchar(MAX) NOT NULL,
	[State] int NOT NULL,
	[Paragraph] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Paragraphs]([Id])
	CONSTRAINT UQ__ParagraphStatesState UNIQUE NONCLUSTERED ([State], [Paragraph])
)

CREATE TABLE [dbo].[Nouns] (
	[Id] int PRIMARY KEY IDENTITY,
	[Text] varchar(MAX) NOT NULL,
	[ParagraphState] int NOT NULL FOREIGN KEY REFERENCES [dbo].[ParagraphStates]([Id])
)

CREATE TABLE [dbo].[VerbTypes] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL
)

INSERT INTO [dbo].[VerbTypes] ([Name])
VALUES ('Look')

INSERT INTO [dbo].[VerbTypes] ([Name])
VALUES ('Interact')

INSERT INTO [dbo].[VerbTypes] ([Name])
VALUES ('With')

INSERT INTO [dbo].[VerbTypes] ([Name])
VALUES ('Talk')

INSERT INTO [dbo].[VerbTypes] ([Name])
VALUES ('Take')

INSERT INTO [dbo].[VerbTypes] ([Name])
VALUES ('Move')

CREATE TABLE [dbo].[Verbs] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[VerbType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[VerbTypes]([Id])
)

CREATE TABLE [dbo].[ResultTypes] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL
)

DECLARE @roomXyzMovementResultTypeName varchar(500)
SET @roomXyzMovementResultTypeName = 'Room XYZ Movement'
DECLARE @roomXyzMovementResultTypeId int
INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES (@roomXyzMovementResultTypeName)
SELECT @roomXyzMovementResultTypeId = SCOPE_IDENTITY()

DECLARE @roomXyzTeleportResultTypeName varchar(500)
SET @roomXyzTeleportResultTypeName = 'Room XYZ Teleport'
DECLARE @roomXyzTeleportResultTypeId int
INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES (@roomXyzTeleportResultTypeName)
SELECT @roomXyzTeleportResultTypeId = SCOPE_IDENTITY()

DECLARE @roomIdTeleportResultTypeName varchar(500)
SET @roomIdTeleportResultTypeName = 'Room Id Teleport'
DECLARE @roomIdTeleportResultTypeId int
INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES (@roomIdTeleportResultTypeName)
SELECT @roomIdTeleportResultTypeId = SCOPE_IDENTITY()

DECLARE @areaIdRoomXyzTeleportResultTypeName varchar(500)
SET @areaIdRoomXyzTeleportResultTypeName = 'Area Id Room XYZ Teleport'
DECLARE @areaIdRoomXyzTeleportResultTypeId int
INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES (@areaIdRoomXyzTeleportResultTypeName)
SELECT @areaIdRoomXyzTeleportResultTypeId = SCOPE_IDENTITY()

DECLARE @areaIdRoomIdTeleportResultTypeName varchar(500)
SET @areaIdRoomIdTeleportResultTypeName = 'Area Id Room Id Teleport'
DECLARE @areaIdRoomIdTeleportResultTypeId int
INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES (@areaIdRoomIdTeleportResultTypeName)
SELECT @areaIdRoomIdTeleportResultTypeId = SCOPE_IDENTITY()

DECLARE @itemAcquisitionResultTypeName varchar(500)
SET @itemAcquisitionResultTypeName = 'Item Acquisition'
DECLARE @itemAcquisitionResultTypeId int
INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES (@itemAcquisitionResultTypeName)
SELECT @itemAcquisitionResultTypeId = SCOPE_IDENTITY()

DECLARE @eventAcquisitionResultTypeName varchar(500)
SET @eventAcquisitionResultTypeName = 'Event Acquisition'
DECLARE @eventAcquisitionResultTypeId int
INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES (@eventAcquisitionResultTypeName)
SELECT @eventAcquisitionResultTypeId = SCOPE_IDENTITY()

DECLARE @characterAcquisitionResultTypeName varchar(500)
SET @characterAcquisitionResultTypeName = 'Character Acquisition'
DECLARE @characterAcquisitionResultTypeId int
INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES (@characterAcquisitionResultTypeName)
SELECT @characterAcquisitionResultTypeId = SCOPE_IDENTITY()

DECLARE @paragraphStateChangeResultTypeName varchar(500)
SET @paragraphStateChangeResultTypeName = 'Paragraph State Change'
DECLARE @paragraphStateChangeResultTypeId int
INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES (@paragraphStateChangeResultTypeName)
SELECT @paragraphStateChangeResultTypeId = SCOPE_IDENTITY()

DECLARE @roomStateChangeResultTypeName varchar(500)
SET @roomStateChangeResultTypeName = 'Room State Change'
DECLARE @roomStateChangeResultTypeId int
INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES (@roomStateChangeResultTypeName)
SELECT @roomStateChangeResultTypeId = SCOPE_IDENTITY()

DECLARE @messageActivationResultTypeName varchar(500)
SET @messageActivationResultTypeName = 'Message Activation'
DECLARE @messageActivationResultTypeId int
INSERT INTO [dbo].[ResultTypes] ([Name])
VALUES (@messageActivationResultTypeName)
SELECT @messageActivationResultTypeId = SCOPE_IDENTITY()

CREATE TABLE [dev].[ResultTypeJSONProperties] (
	[Id] int PRIMARY KEY IDENTITY,
	[JSONProperty] varchar(MAX) NOT NULL,
	[ResultType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[ResultTypes]([Id])
)

INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('xDir', @roomXyzMovementResultTypeId)
INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('yDir', @roomXyzMovementResultTypeId)
INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('zDir', @roomXyzMovementResultTypeId)

INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('xPos', @roomXyzTeleportResultTypeId)
INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('yPos', @roomXyzTeleportResultTypeId)
INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('zPos', @roomXyzTeleportResultTypeId)

INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('roomId', @roomIdTeleportResultTypeId)

INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('areaId', @areaIdRoomXyzTeleportResultTypeId)
INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('xPos', @areaIdRoomXyzTeleportResultTypeId)
INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('yPos', @areaIdRoomXyzTeleportResultTypeId)
INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('zPos', @areaIdRoomXyzTeleportResultTypeId)

INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('areaId', @areaIdRoomIdTeleportResultTypeId)
INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('roomId', @areaIdRoomIdTeleportResultTypeId)

INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('itemId', @itemAcquisitionResultTypeId)

INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('eventId', @eventAcquisitionResultTypeId)

INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('characterId', @characterAcquisitionResultTypeId)

INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('paragraphStateId', @paragraphStateChangeResultTypeId)
INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('paragraphState', @paragraphStateChangeResultTypeId)

INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('roomStateId', @roomStateChangeResultTypeId)
INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('roomState', @roomStateChangeResultTypeId)

INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
VALUES ('messageId', @messageActivationResultTypeId)

CREATE TABLE [dbo].[Results] (
	[Id] int PRIMARY KEY IDENTITY,
	[JSONData] varchar(MAX) NULL,
	[ResultType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[ResultTypes]([Id])
)

CREATE TABLE [dev].[ResultNames] (
	[Result] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Results]([Id]),
	[Name] varchar(500) NOT NULL
)

DECLARE @move_Y_North1ResultName varchar(500)
DECLARE @move_Y_North1ResultJSONData varchar(MAX)
DECLARE @move_Y_North1ResultId int
SET @move_Y_North1ResultName = 'Move_Y_North1'
SET @move_Y_North1ResultJSONData = '{ "xDir":"0", "yDir":"-1", "zDir":"0" }'
INSERT INTO [dbo].[Results] ([JSONData], [ResultType])
VALUES (@move_Y_North1ResultJSONData, @roomXyzMovementResultTypeId)
SELECT @move_Y_North1ResultId = SCOPE_IDENTITY()
INSERT INTO [dev].[ResultNames] ([Result], [Name])
VALUES (@move_Y_North1ResultId, @move_Y_North1ResultName)

DECLARE @move_Y_South1ResultName varchar(500)
DECLARE @move_Y_South1ResultJSONData varchar(MAX)
DECLARE @move_Y_South1ResultId int
SET @move_Y_South1ResultName = 'Move_Y_South1'
SET @move_Y_South1ResultJSONData = '{ "xDir":"0", "yDir":"1", "zDir":"0" }'
INSERT INTO [dbo].[Results] ([JSONData], [ResultType])
VALUES (@move_Y_South1ResultJSONData, @roomXyzMovementResultTypeId)
SELECT @move_Y_South1ResultId = SCOPE_IDENTITY()
INSERT INTO [dev].[ResultNames] ([Result], [Name])
VALUES (@move_Y_South1ResultId, @move_Y_South1ResultName)

DECLARE @move_X_West1ResultName varchar(500)
DECLARE @move_X_West1ResultJSONData varchar(MAX)
DECLARE @move_X_West1ResultId int
SET @move_X_West1ResultName = 'Move_X_West1'
SET @move_X_West1ResultJSONData = '{ "xDir":"-1", "yDir":"0", "zDir":"0" }'
INSERT INTO [dbo].[Results] ([JSONData], [ResultType])
VALUES (@move_X_West1ResultJSONData, @roomXyzMovementResultTypeId)
SELECT @move_X_West1ResultId = SCOPE_IDENTITY()
INSERT INTO [dev].[ResultNames] ([Result], [Name])
VALUES (@move_X_West1ResultId, @move_X_West1ResultName)

DECLARE @move_X_East1ResultName varchar(500)
DECLARE @move_X_East1ResultJSONData varchar(MAX)
DECLARE @move_X_East1ResultId int
SET @move_X_East1ResultName = 'Move_X_East1'
SET @move_X_East1ResultJSONData = '{ "xDir":"1", "yDir":"0", "zDir":"0" }'
INSERT INTO [dbo].[Results] ([JSONData], [ResultType])
VALUES (@move_X_East1ResultJSONData, @roomXyzMovementResultTypeId)
SELECT @move_X_East1ResultId = SCOPE_IDENTITY()
INSERT INTO [dev].[ResultNames] ([Result], [Name])
VALUES (@move_X_East1ResultId, @move_X_East1ResultName)

DECLARE @move_Z_Up1ResultName varchar(500)
DECLARE @move_Z_Up1ResultJSONData varchar(MAX)
DECLARE @move_Z_Up1ResultId int
SET @move_Z_Up1ResultName = 'Move_Z_Up1'
SET @move_Z_Up1ResultJSONData = '{ "xDir":"0", "yDir":"0", "zDir":"1" }'
INSERT INTO [dbo].[Results] ([JSONData], [ResultType])
VALUES (@move_Z_Up1ResultJSONData, @roomXyzMovementResultTypeId)
SELECT @move_Z_Up1ResultId = SCOPE_IDENTITY()
INSERT INTO [dev].[ResultNames] ([Result], [Name])
VALUES (@move_Z_Up1ResultId, @move_Z_Up1ResultName)

DECLARE @move_Z_Down1ResultName varchar(500)
DECLARE @move_Z_Down1ResultJSONData varchar(MAX)
DECLARE @move_Z_Down1ResultId int
SET @move_Z_Down1ResultName = 'Move_Z_Down1'
SET @move_Z_Down1ResultJSONData = '{ "xDir":"0", "yDir":"0", "zDir":"-1" }'
INSERT INTO [dbo].[Results] ([JSONData], [ResultType])
VALUES (@move_Z_Down1ResultJSONData, @roomXyzMovementResultTypeId)
SELECT @move_Z_Down1ResultId = SCOPE_IDENTITY()
INSERT INTO [dev].[ResultNames] ([Result], [Name])
VALUES (@move_Z_Down1ResultId, @move_Z_Down1ResultName)

CREATE TABLE [dbo].[Actions] (
	[Id] int PRIMARY KEY IDENTITY,
	[VerbType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[VerbTypes]([Id]),
	[Noun] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Nouns]([Id])
)

CREATE TABLE [dbo].[ActionResults] (
	[Id] int PRIMARY KEY IDENTITY,
	[Action] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Actions]([Id]),
	[Result] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Results]([Id])
)

CREATE TABLE [dbo].[Items] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[Description] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[Events] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[Description] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[Characters] (
	[Id] int PRIMARY KEY IDENTITY,
	[Name] varchar(500) NOT NULL,
	[Description] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[ItemActionRequirements] (
	[Id] int PRIMARY KEY IDENTITY,
	[Item] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Items]([Id]),
	[Action] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Actions]([Id])
)

CREATE TABLE [dbo].[EventActionRequirements] (
	[Id] int PRIMARY KEY IDENTITY,
	[Event] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Events]([Id]),
	[Action] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Actions]([Id])
)

CREATE TABLE [dbo].[CharacterActionRequirements] (
	[Id] int PRIMARY KEY IDENTITY,
	[Character] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Characters]([Id]),
	[Action] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Actions]([Id])
)

CREATE TABLE [dbo].[Messages] (
	[Id] int PRIMARY KEY IDENTITY,
	[Text] varchar(MAX) NOT NULL
)

CREATE TABLE [dev].[MessageNames] (
	[Message] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Messages]([Id]),
	[Name] varchar(500) NOT NULL
)

CREATE TABLE [dbo].[MessageChoices] (
	[Id] int PRIMARY KEY IDENTITY,
	[Text] varchar(MAX) NOT NULL,
	[Message] int FOREIGN KEY REFERENCES [dbo].[Messages]([Id])
)

CREATE TABLE [dev].[MessageChoiceNames] (
	[MessageChoice] int NOT NULL FOREIGN KEY REFERENCES [dbo].[MessageChoices]([Id]),
	[Name] varchar(500) NOT NULL
)

CREATE TABLE [dbo].[MessageChoiceResults] (
	[Id] int PRIMARY KEY IDENTITY,
	[Result] int NULL FOREIGN KEY REFERENCES [dbo].[Results]([Id]),
	[MessageChoice] int FOREIGN KEY REFERENCES [dbo].[MessageChoices]([Id])
)

CREATE TABLE [dbo].[EmailUserNames] (
	[Id] int PRIMARY KEY IDENTITY,
	[UserName] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[EmailDomainNames] (
	[Id] int PRIMARY KEY IDENTITY,
	[DomainName] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[EmailDomains] (
	[Id] int PRIMARY KEY IDENTITY,
	[Domain] varchar(MAX) NOT NULL
)

CREATE TABLE [dbo].[Players] (
	[EmailUserName] int NOT NULL FOREIGN KEY REFERENCES [dbo].[EmailUserNames]([Id]),
	[EmailDomainName] int NOT NULL FOREIGN KEY REFERENCES [dbo].[EmailDomainNames]([Id]),
	[EmailDomain] int NOT NULL FOREIGN KEY REFERENCES [dbo].[EmailDomains]([Id]),
	[Password] varchar(MAX) NOT NULL,
	[Id] uniqueidentifier NOT NULL PRIMARY KEY,
	[LastCheckpoint] datetime NOT NULL
)

CREATE TABLE [dbo].[PlayerRoomStates] (
	[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
	[Room] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id]),
	[RoomState] int NOT NULL FOREIGN KEY REFERENCES [dbo].[RoomStates]([Id]),
	[CheckpointDate] datetime NOT NULL
)

CREATE TABLE [dbo].[PlayerParagraphStates] (
	[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
	[Paragraph] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Paragraphs]([Id]),
	[ParagraphStates] int NOT NULL FOREIGN KEY REFERENCES [dbo].[ParagraphStates]([Id]),
	[CheckpointDate] datetime NOT NULL
)

CREATE TABLE [dbo].[PlayerInventory] (
	[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
	[Item] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Items]([Id]),
	[Active] bit NOT NULL,
	[CheckpointDate] datetime NOT NULL
)

CREATE TABLE [dbo].[PlayerHistory] (
	[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
	[Event] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Events]([Id]),
	[CheckpointDate] datetime NOT NULL
)

CREATE TABLE [dbo].[PlayerParty] (
	[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
	[Character] int NOT NULL FOREIGN KEY REFERENCES [dbo].[characters]([Id]),
	[Active] bit NOT NULL,
	[CheckpointDate] datetime NOT NULL
)

GO

CREATE VIEW [dev].[Results] AS
	SELECT r.[Id],
		   ISNULL(rn.[Name], '') AS [Name],
		   r.[JSONData],
		   r.[ResultType]
	FROM [dbo].[Results] r
	LEFT JOIN [dev].[ResultNames] rn
	ON rn.[Result] = r.[Id]
	
GO

CREATE VIEW [dev].[Messages] AS
	SELECT m.[Id],
		   ISNULL(mn.[Name], '') AS [Name],
		   m.[Text]
	FROM [dbo].[Messages] m
	LEFT JOIN [dev].[MessageNames] mn
	ON mn.[Message] = m.[Id]
	
GO

CREATE VIEW [dev].[MessageChoices] AS
	SELECT m.[Id],
		   ISNULL(mn.[Name], '') AS [Name],
		   m.[Text],
		   m.[Message]
	FROM [dbo].[MessageChoices] m
	LEFT JOIN [dev].[MessageChoiceNames] mn
	ON mn.[MessageChoice] = m.[Id]
	
GO

CREATE VIEW [dev].[ActionNames] AS
	SELECT a.[Id] AS [Action],
		   vt.[Name] + ' on ' + n.[Text] AS [Name]
	FROM [dbo].[Actions] a
	INNER JOIN [dbo].[VerbTypes] vt
	ON a.[VerbType] = vt.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	
GO

CREATE VIEW [dev].[ActionResultTypes] AS
	SELECT a.[Id] as [Action],
		   rt.[Id] as [ResultType]
	FROM [dbo].[ResultTypes] rt 
	INNER JOIN [dbo].[Results] r
	ON rt.[Id] = r.[ResultType]
	INNER JOIN [dbo].[ActionResults] ar
	ON ar.[Result] = r.[Id]
	INNER JOIN [dbo].[Actions] a
	on a.[Id] = ar.[Action]
	
GO

CREATE VIEW [dev].[MessageChoiceResultTypes] AS
	SELECT a.[Id] as [MessageChoice],
		   rt.[Id] as [ResultType]
	FROM [dbo].[ResultTypes] rt 
	INNER JOIN [dbo].[Results] r
	ON rt.[Id] = r.[ResultType]
	INNER JOIN [dbo].[MessageChoiceResults] ar
	ON ar.[Result] = r.[Id]
	INNER JOIN [dbo].[MessageChoices] a
	on a.[Id] = ar.[MessageChoice]
	
GO