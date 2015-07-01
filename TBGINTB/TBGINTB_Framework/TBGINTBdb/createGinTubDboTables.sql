USE [GinTub]

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'Areas')
BEGIN
	CREATE TABLE [dbo].[Areas] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[Name] varchar(256) NOT NULL
	)
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'Locations')
	CREATE TABLE [dbo].[Locations] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[Name] varchar(256) NOT NULL,
		[LocationFile] varchar(256) NOT NULL
	)

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'Rooms')
BEGIN
	CREATE TABLE [dbo].[Rooms] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[Name] varchar(256) NOT NULL,
		[X] int NOT NULL,
		[Y] int NOT NULL,
		[Z] int NOT NULL,
		[Area] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Areas]([Id])
	)
	CREATE UNIQUE NONCLUSTERED INDEX IX__Rooms__AreaXYZ ON [dbo].[Rooms]([Area], [X], [Y], [Z])
	INCLUDE([Name])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'RoomStates')
BEGIN
	CREATE TABLE [dbo].[RoomStates] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[State] int NOT NULL,
		[Time] datetime NULL,
		[Location] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Locations]([Id]),
		[Room] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id])
	)
	CREATE UNIQUE NONCLUSTERED INDEX IX__RoomStates__RoomState ON [dbo].[RoomStates]([Room], [State])
	INCLUDE([Time], [Location])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'Paragraphs')
BEGIN
	CREATE TABLE [dbo].[Paragraphs] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[Order] int NOT NULL,
		[Room] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id]),
		[RoomState] int NULL FOREIGN KEY REFERENCES [dbo].[RoomStates]([Id]),
		CONSTRAINT UQ__Paragraphs UNIQUE NONCLUSTERED ([Order], [Room], [RoomState])
	)
	CREATE NONCLUSTERED INDEX IX__Paragraphs__RoomRoomState ON [dbo].[Paragraphs]([Room], [RoomState])
	INCLUDE([Order])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'ParagraphStates')
BEGIN
	CREATE TABLE [dbo].[ParagraphStates] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[Text] varchar(256) NOT NULL,
		[State] int NOT NULL,
		[Paragraph] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Paragraphs]([Id]),
		CONSTRAINT UQ__ParagraphStates UNIQUE NONCLUSTERED ([State], [Paragraph])
	)
	CREATE NONCLUSTERED INDEX IX__ParagraphStates__ParagraphState ON [dbo].[ParagraphStates]([Paragraph], [State])
	INCLUDE([Text])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'Nouns')
BEGIN
	CREATE TABLE [dbo].[Nouns] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[Text] varchar(256) NOT NULL,
		[ParagraphState] int NOT NULL FOREIGN KEY REFERENCES [dbo].[ParagraphStates]([Id])
	)
	CREATE NONCLUSTERED INDEX IX__Nouns__ParagraphState ON [dbo].[Nouns]([ParagraphState])
	INCLUDE([Text])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'VerbTypes')
	CREATE TABLE [dbo].[VerbTypes] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[Name] varchar(256) NOT NULL
	)

IF NOT EXISTS (SELECT 1 FROM [dbo].[VerbTypes] WHERE [Name] = 'Look')
	INSERT INTO [dbo].[VerbTypes] ([Name])
	VALUES ('Look')

IF NOT EXISTS (SELECT 1 FROM [dbo].[VerbTypes] WHERE [Name] = 'Interact')
	INSERT INTO [dbo].[VerbTypes] ([Name])
	VALUES ('Interact')

IF NOT EXISTS (SELECT 1 FROM [dbo].[VerbTypes] WHERE [Name] = 'With')
	INSERT INTO [dbo].[VerbTypes] ([Name])
	VALUES ('With')

IF NOT EXISTS (SELECT 1 FROM [dbo].[VerbTypes] WHERE [Name] = 'Talk')
	INSERT INTO [dbo].[VerbTypes] ([Name])
	VALUES ('Talk')

IF NOT EXISTS (SELECT 1 FROM [dbo].[VerbTypes] WHERE [Name] = 'Take')
	INSERT INTO [dbo].[VerbTypes] ([Name])
	VALUES ('Take')

IF NOT EXISTS (SELECT 1 FROM [dbo].[VerbTypes] WHERE [Name] = 'Move')
	INSERT INTO [dbo].[VerbTypes] ([Name])
	VALUES ('Move')

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'Verbs')
BEGIN
	CREATE TABLE [dbo].[Verbs] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[Name] varchar(256) NOT NULL,
		[VerbType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[VerbTypes]([Id])
	)
	CREATE NONCLUSTERED INDEX IX__Verbs__VerbType ON [dbo].[Verbs]([VerbType])
	INCLUDE([Name])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'ResultTypes')
	CREATE TABLE [dbo].[ResultTypes] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[Name] varchar(256) NOT NULL
	)

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dev' and t.[name] = 'ResultTypeJSONProperties')
BEGIN
	CREATE TABLE [dev].[ResultTypeJSONProperties] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[JSONProperty] varchar(256) NOT NULL,
		[ResultType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[ResultTypes]([Id])
	)
	CREATE NONCLUSTERED INDEX IX__ResultTypeJSONProperties__ResultType ON [dev].[ResultTypeJSONProperties]([ResultType])
	INCLUDE([JSONProperty])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'Results')
BEGIN
	CREATE TABLE [dbo].[Results] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[JSONData] varchar(500) NULL,
		[ResultType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[ResultTypes]([Id])
	)
	CREATE NONCLUSTERED INDEX IX__Results__ResultType ON [dbo].[Results]([ResultType])
	INCLUDE([JSONData])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dev' and t.[name] = 'ResultNames')
BEGIN
	CREATE TABLE [dev].[ResultNames] (
		[Result] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Results]([Id]),
		[Name] varchar(256) NOT NULL
	)
	CREATE UNIQUE CLUSTERED INDEX IX__ResultNames__Result ON [dev].[ResultNames]([Result])
END

IF NOT EXISTS (SELECT 1 FROM [dbo].[ResultTypes] WHERE [Name] = 'Room XYZ Movement')
BEGIN
	DECLARE @roomXyzMovementResultTypeName varchar(256)
	SET @roomXyzMovementResultTypeName = 'Room XYZ Movement'
	DECLARE @roomXyzMovementResultTypeId int
	INSERT INTO [dbo].[ResultTypes] ([Name])
	VALUES (@roomXyzMovementResultTypeName)
	SELECT @roomXyzMovementResultTypeId = SCOPE_IDENTITY()

	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('xDir', @roomXyzMovementResultTypeId)
	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('yDir', @roomXyzMovementResultTypeId)
	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('zDir', @roomXyzMovementResultTypeId)

	DECLARE @move_Y_North1ResultName varchar(256)
	DECLARE @move_Y_North1ResultJSONData varchar(256)
	DECLARE @move_Y_North1ResultId int
	SET @move_Y_North1ResultName = 'Move_Y_North1'
	SET @move_Y_North1ResultJSONData = '{ "xDir":"0", "yDir":"-1", "zDir":"0" }'
	INSERT INTO [dbo].[Results] ([JSONData], [ResultType])
	VALUES (@move_Y_North1ResultJSONData, @roomXyzMovementResultTypeId)
	SELECT @move_Y_North1ResultId = SCOPE_IDENTITY()
	INSERT INTO [dev].[ResultNames] ([Result], [Name])
	VALUES (@move_Y_North1ResultId, @move_Y_North1ResultName)

	DECLARE @move_Y_South1ResultName varchar(256)
	DECLARE @move_Y_South1ResultJSONData varchar(256)
	DECLARE @move_Y_South1ResultId int
	SET @move_Y_South1ResultName = 'Move_Y_South1'
	SET @move_Y_South1ResultJSONData = '{ "xDir":"0", "yDir":"1", "zDir":"0" }'
	INSERT INTO [dbo].[Results] ([JSONData], [ResultType])
	VALUES (@move_Y_South1ResultJSONData, @roomXyzMovementResultTypeId)
	SELECT @move_Y_South1ResultId = SCOPE_IDENTITY()
	INSERT INTO [dev].[ResultNames] ([Result], [Name])
	VALUES (@move_Y_South1ResultId, @move_Y_South1ResultName)

	DECLARE @move_X_West1ResultName varchar(256)
	DECLARE @move_X_West1ResultJSONData varchar(256)
	DECLARE @move_X_West1ResultId int
	SET @move_X_West1ResultName = 'Move_X_West1'
	SET @move_X_West1ResultJSONData = '{ "xDir":"-1", "yDir":"0", "zDir":"0" }'
	INSERT INTO [dbo].[Results] ([JSONData], [ResultType])
	VALUES (@move_X_West1ResultJSONData, @roomXyzMovementResultTypeId)
	SELECT @move_X_West1ResultId = SCOPE_IDENTITY()
	INSERT INTO [dev].[ResultNames] ([Result], [Name])
	VALUES (@move_X_West1ResultId, @move_X_West1ResultName)

	DECLARE @move_X_East1ResultName varchar(256)
	DECLARE @move_X_East1ResultJSONData varchar(256)
	DECLARE @move_X_East1ResultId int
	SET @move_X_East1ResultName = 'Move_X_East1'
	SET @move_X_East1ResultJSONData = '{ "xDir":"1", "yDir":"0", "zDir":"0" }'
	INSERT INTO [dbo].[Results] ([JSONData], [ResultType])
	VALUES (@move_X_East1ResultJSONData, @roomXyzMovementResultTypeId)
	SELECT @move_X_East1ResultId = SCOPE_IDENTITY()
	INSERT INTO [dev].[ResultNames] ([Result], [Name])
	VALUES (@move_X_East1ResultId, @move_X_East1ResultName)

	DECLARE @move_Z_Up1ResultName varchar(256)
	DECLARE @move_Z_Up1ResultJSONData varchar(256)
	DECLARE @move_Z_Up1ResultId int
	SET @move_Z_Up1ResultName = 'Move_Z_Up1'
	SET @move_Z_Up1ResultJSONData = '{ "xDir":"0", "yDir":"0", "zDir":"1" }'
	INSERT INTO [dbo].[Results] ([JSONData], [ResultType])
	VALUES (@move_Z_Up1ResultJSONData, @roomXyzMovementResultTypeId)
	SELECT @move_Z_Up1ResultId = SCOPE_IDENTITY()
	INSERT INTO [dev].[ResultNames] ([Result], [Name])
	VALUES (@move_Z_Up1ResultId, @move_Z_Up1ResultName)

	DECLARE @move_Z_Down1ResultName varchar(256)
	DECLARE @move_Z_Down1ResultJSONData varchar(256)
	DECLARE @move_Z_Down1ResultId int
	SET @move_Z_Down1ResultName = 'Move_Z_Down1'
	SET @move_Z_Down1ResultJSONData = '{ "xDir":"0", "yDir":"0", "zDir":"-1" }'
	INSERT INTO [dbo].[Results] ([JSONData], [ResultType])
	VALUES (@move_Z_Down1ResultJSONData, @roomXyzMovementResultTypeId)
	SELECT @move_Z_Down1ResultId = SCOPE_IDENTITY()
	INSERT INTO [dev].[ResultNames] ([Result], [Name])
	VALUES (@move_Z_Down1ResultId, @move_Z_Down1ResultName)
END

IF NOT EXISTS (SELECT 1 FROM [dbo].[ResultTypes] WHERE [Name] = 'Room XYZ Teleport')
BEGIN
	DECLARE @roomXyzTeleportResultTypeName varchar(256)
	SET @roomXyzTeleportResultTypeName = 'Room XYZ Teleport'
	DECLARE @roomXyzTeleportResultTypeId int
	INSERT INTO [dbo].[ResultTypes] ([Name])
	VALUES (@roomXyzTeleportResultTypeName)
	SELECT @roomXyzTeleportResultTypeId = SCOPE_IDENTITY()

	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('xPos', @roomXyzTeleportResultTypeId)
	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('yPos', @roomXyzTeleportResultTypeId)
	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('zPos', @roomXyzTeleportResultTypeId)
END

IF NOT EXISTS (SELECT 1 FROM [dbo].[ResultTypes] WHERE [Name] = 'Room Id Teleport')
BEGIN
	DECLARE @roomIdTeleportResultTypeName varchar(256)
	SET @roomIdTeleportResultTypeName = 'Room Id Teleport'
	DECLARE @roomIdTeleportResultTypeId int
	INSERT INTO [dbo].[ResultTypes] ([Name])
	VALUES (@roomIdTeleportResultTypeName)
	SELECT @roomIdTeleportResultTypeId = SCOPE_IDENTITY()

	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('roomId', @roomIdTeleportResultTypeId)
END

IF NOT EXISTS (SELECT 1 FROM [dbo].[ResultTypes] WHERE [Name] = 'Area Id Room XYZ Teleport')
BEGIN
	DECLARE @areaIdRoomXyzTeleportResultTypeName varchar(256)
	SET @areaIdRoomXyzTeleportResultTypeName = 'Area Id Room XYZ Teleport'
	DECLARE @areaIdRoomXyzTeleportResultTypeId int
	INSERT INTO [dbo].[ResultTypes] ([Name])
	VALUES (@areaIdRoomXyzTeleportResultTypeName)
	SELECT @areaIdRoomXyzTeleportResultTypeId = SCOPE_IDENTITY()

	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('areaId', @areaIdRoomXyzTeleportResultTypeId)
	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('xPos', @areaIdRoomXyzTeleportResultTypeId)
	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('yPos', @areaIdRoomXyzTeleportResultTypeId)
	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('zPos', @areaIdRoomXyzTeleportResultTypeId)
END

IF NOT EXISTS (SELECT 1 FROM [dbo].[ResultTypes] WHERE [Name] = 'Area Id Room Id Teleport')
BEGIN
	DECLARE @areaIdRoomIdTeleportResultTypeName varchar(256)
	SET @areaIdRoomIdTeleportResultTypeName = 'Area Id Room Id Teleport'
	DECLARE @areaIdRoomIdTeleportResultTypeId int
	INSERT INTO [dbo].[ResultTypes] ([Name])
	VALUES (@areaIdRoomIdTeleportResultTypeName)
	SELECT @areaIdRoomIdTeleportResultTypeId = SCOPE_IDENTITY()

	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('areaId', @areaIdRoomIdTeleportResultTypeId)
	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('roomId', @areaIdRoomIdTeleportResultTypeId)
END

IF NOT EXISTS (SELECT 1 FROM [dbo].[ResultTypes] WHERE [Name] = 'Item Acquisition')
BEGIN
	DECLARE @itemAcquisitionResultTypeName varchar(256)
	SET @itemAcquisitionResultTypeName = 'Item Acquisition'
	DECLARE @itemAcquisitionResultTypeId int
	INSERT INTO [dbo].[ResultTypes] ([Name])
	VALUES (@itemAcquisitionResultTypeName)
	SELECT @itemAcquisitionResultTypeId = SCOPE_IDENTITY()

	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('itemId', @itemAcquisitionResultTypeId)
END

IF NOT EXISTS (SELECT 1 FROM [dbo].[ResultTypes] WHERE [Name] = 'Event Acquisition')
BEGIN
	DECLARE @eventAcquisitionResultTypeName varchar(256)
	SET @eventAcquisitionResultTypeName = 'Event Acquisition'
	DECLARE @eventAcquisitionResultTypeId int
	INSERT INTO [dbo].[ResultTypes] ([Name])
	VALUES (@eventAcquisitionResultTypeName)
	SELECT @eventAcquisitionResultTypeId = SCOPE_IDENTITY()

	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('eventId', @eventAcquisitionResultTypeId)
END

IF NOT EXISTS (SELECT 1 FROM [dbo].[ResultTypes] WHERE [Name] = 'Character Acquisition')
BEGIN
	DECLARE @characterAcquisitionResultTypeName varchar(256)
	SET @characterAcquisitionResultTypeName = 'Character Acquisition'
	DECLARE @characterAcquisitionResultTypeId int
	INSERT INTO [dbo].[ResultTypes] ([Name])
	VALUES (@characterAcquisitionResultTypeName)
	SELECT @characterAcquisitionResultTypeId = SCOPE_IDENTITY()

	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('characterId', @characterAcquisitionResultTypeId)
END

IF NOT EXISTS (SELECT 1 FROM [dbo].[ResultTypes] WHERE [Name] = 'Paragraph State Change')
BEGIN
	DECLARE @paragraphStateChangeResultTypeName varchar(256)
	SET @paragraphStateChangeResultTypeName = 'Paragraph State Change'
	DECLARE @paragraphStateChangeResultTypeId int
	INSERT INTO [dbo].[ResultTypes] ([Name])
	VALUES (@paragraphStateChangeResultTypeName)
	SELECT @paragraphStateChangeResultTypeId = SCOPE_IDENTITY()

	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('paragraphId', @paragraphStateChangeResultTypeId)
	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('state', @paragraphStateChangeResultTypeId)
END

IF NOT EXISTS (SELECT 1 FROM [dbo].[ResultTypes] WHERE [Name] = 'Room State Change')
BEGIN
	DECLARE @roomStateChangeResultTypeName varchar(256)
	SET @roomStateChangeResultTypeName = 'Room State Change'
	DECLARE @roomStateChangeResultTypeId int
	INSERT INTO [dbo].[ResultTypes] ([Name])
	VALUES (@roomStateChangeResultTypeName)
	SELECT @roomStateChangeResultTypeId = SCOPE_IDENTITY()

	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('roomId', @roomStateChangeResultTypeId)
	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('state', @roomStateChangeResultTypeId)
END

IF NOT EXISTS (SELECT 1 FROM [dbo].[ResultTypes] WHERE [Name] = 'Message Activation')
BEGIN
	DECLARE @messageActivationResultTypeName varchar(256)
	SET @messageActivationResultTypeName = 'Message Activation'
	DECLARE @messageActivationResultTypeId int
	INSERT INTO [dbo].[ResultTypes] ([Name])
	VALUES (@messageActivationResultTypeName)
	SELECT @messageActivationResultTypeId = SCOPE_IDENTITY()

	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES ('messageId', @messageActivationResultTypeId)
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'Actions')
BEGIN
	CREATE TABLE [dbo].[Actions] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[VerbType] int NOT NULL FOREIGN KEY REFERENCES [dbo].[VerbTypes]([Id]),
		[Noun] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Nouns]([Id])
	)
	CREATE NONCLUSTERED INDEX IX__Actions__NounVerbType ON [dbo].[Actions]([Noun], [VerbType])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'ActionResults')
BEGIN
	CREATE TABLE [dbo].[ActionResults] (
		[Id] int PRIMARY KEY NONCLUSTERED IDENTITY,
		[Action] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Actions]([Id]),
		[Result] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Results]([Id]),
	)
	CREATE CLUSTERED INDEX IX__ActionResults__Clustered ON [dbo].[ActionResults]([Action])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'Items')
	CREATE TABLE [dbo].[Items] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[Name] varchar(256) NOT NULL,
		[Description] varchar(256) NOT NULL
	)

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'Events')
	CREATE TABLE [dbo].[Events] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[Name] varchar(256) NOT NULL,
		[Description] varchar(256) NOT NULL
	)

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'Characters')
	CREATE TABLE [dbo].[Characters] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[Name] varchar(256) NOT NULL,
		[Description] varchar(256) NOT NULL
	)

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'ItemActionRequirements')
BEGIN
	CREATE TABLE [dbo].[ItemActionRequirements] (
		[Id] int PRIMARY KEY NONCLUSTERED IDENTITY,
		[Item] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Items]([Id]),
		[Action] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Actions]([Id])
	)
	CREATE CLUSTERED INDEX IX__ItemActionRequirements__Clustered ON [dbo].[ItemActionRequirements]([Action])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'EventActionRequirements')
BEGIN
	CREATE TABLE [dbo].[EventActionRequirements] (
		[Id] int PRIMARY KEY NONCLUSTERED IDENTITY,
		[Event] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Events]([Id]),
		[Action] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Actions]([Id])
	)
	CREATE CLUSTERED INDEX IX__EventActionRequirements__Clustered ON [dbo].[EventActionRequirements]([Action])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'CharacterActionRequirements')
BEGIN
	CREATE TABLE [dbo].[CharacterActionRequirements] (
		[Id] int PRIMARY KEY NONCLUSTERED IDENTITY,
		[Character] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Characters]([Id]),
		[Action] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Actions]([Id])
	)
	CREATE CLUSTERED INDEX IX__CharacterActionRequirements__Clustered ON [dbo].[CharacterActionRequirements]([Action])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'Messages')
	CREATE TABLE [dbo].[Messages] (
		[Id] int PRIMARY KEY CLUSTERED IDENTITY,
		[Text] varchar(256) NOT NULL
	)

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dev' and t.[name] = 'MessageNames')
BEGIN
	CREATE TABLE [dev].[MessageNames] (
		[Message] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Messages]([Id]),
		[Name] varchar(256) NOT NULL
	)
	CREATE UNIQUE CLUSTERED INDEX IX__MessageNames__Message ON [dev].[MessageNames]([Message])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'MessageChoices')
BEGIN
	CREATE TABLE [dbo].[MessageChoices] (
		[Id] int PRIMARY KEY NONCLUSTERED IDENTITY,
		[Text] varchar(256) NOT NULL,
		[Message] int FOREIGN KEY REFERENCES [dbo].[Messages]([Id])
	)
	CREATE CLUSTERED INDEX IX__MessageChoices__Clustered ON [dbo].[MessageChoices]([Message])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dev' and t.[name] = 'MessageChoiceNames')
BEGIN
	CREATE TABLE [dev].[MessageChoiceNames] (
		[MessageChoice] int NOT NULL FOREIGN KEY REFERENCES [dbo].[MessageChoices]([Id]),
		[Name] varchar(256) NOT NULL
	)
	CREATE UNIQUE CLUSTERED INDEX IX__MessageChoiceNames__MessageChoice ON [dev].[MessageChoiceNames]([MessageChoice])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'MessageChoiceResults')
BEGIN
	CREATE TABLE [dbo].[MessageChoiceResults] (
		[Id] int PRIMARY KEY NONCLUSTERED IDENTITY,
		[Result] int NULL FOREIGN KEY REFERENCES [dbo].[Results]([Id]),
		[MessageChoice] int FOREIGN KEY REFERENCES [dbo].[MessageChoices]([Id])
	)
	CREATE CLUSTERED INDEX IX__MessageChoiceResults__Clustered ON [dbo].[MessageChoiceResults]([MessageChoice])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'EmailUserNames')
BEGIN
	CREATE TABLE [dbo].[EmailUserNames] (
		[Id] int PRIMARY KEY NONCLUSTERED IDENTITY,
		[UserName] varchar(256) NOT NULL CONSTRAINT IX__EmailUserNames__Clustered UNIQUE CLUSTERED
	)
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'EmailDomainNames')
	CREATE TABLE [dbo].[EmailDomainNames] (
		[Id] int PRIMARY KEY NONCLUSTERED IDENTITY,
		[DomainName] varchar(256) NOT NULL CONSTRAINT IX__EmailDomainNames__Clustered UNIQUE CLUSTERED
	)

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'EmailDomains')
	CREATE TABLE [dbo].[EmailDomains] (
		[Id] int PRIMARY KEY NONCLUSTERED IDENTITY,
		[Domain] varchar(256) NOT NULL CONSTRAINT IX__DomainNames__Clustered UNIQUE CLUSTERED
	)

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'Players')
BEGIN
	CREATE TABLE [dbo].[Players] (
		[EmailUserName] int NOT NULL FOREIGN KEY REFERENCES [dbo].[EmailUserNames]([Id]),
		[EmailDomainName] int NOT NULL FOREIGN KEY REFERENCES [dbo].[EmailDomainNames]([Id]),
		[EmailDomain] int NOT NULL FOREIGN KEY REFERENCES [dbo].[EmailDomains]([Id]),
		[Password] varchar(256) NOT NULL,
		[Id] uniqueidentifier NOT NULL PRIMARY KEY CLUSTERED,
		[LastCheckpoint] datetime NOT NULL,
		[LastRoom] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id])
	)
	CREATE UNIQUE NONCLUSTERED INDEX IX__Players__Nonclustered ON [dbo].[Players] ([EmailUserName], [EmailDomainName], [EmailDomain], [Password])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'PlayerStatesOfRooms')
BEGIN
	CREATE TABLE [dbo].[PlayerStatesOfRooms] (
		[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
		[Room] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id]),
		[State] int NOT NULL,
		[CheckpointDate] datetime NOT NULL
	)
	CREATE UNIQUE NONCLUSTERED INDEX IX__PlayerStatesOfRooms__Nonclustered ON [dbo].[PlayerStatesOfRooms] ([Player], [Room])
	INCLUDE([State], [CheckpointDate])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'PlayerStatesOfParagraphs')
BEGIN
	CREATE TABLE [dbo].[PlayerStatesOfParagraphs] (
		[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
		[Paragraph] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Paragraphs]([Id]),
		[State] int NOT NULL,
		[CheckpointDate] datetime NOT NULL
	)
	CREATE UNIQUE NONCLUSTERED INDEX IX__PlayerStatesOfParagraphs__Nonclustered ON [dbo].[PlayerStatesOfParagraphs] ([Player], [Paragraph])
	INCLUDE([State], [CheckpointDate])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'PlayerInventory')
BEGIN
	CREATE TABLE [dbo].[PlayerInventory] (
		[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
		[Item] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Items]([Id]),
		[InInventory] bit NOT NULL,
		[CheckpointDate] datetime NOT NULL
	)
	CREATE CLUSTERED INDEX IX__PlayerInventory__Clustered ON [dbo].[PlayerInventory]([Player], [Item])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'PlayerHistory')
BEGIN
	CREATE TABLE [dbo].[PlayerHistory] (
		[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
		[Event] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Events]([Id]),
		[InHistory] bit NOT NULL,
		[CheckpointDate] datetime NOT NULL
	)
	CREATE CLUSTERED INDEX IX__PlayerHistory__Clustered ON [dbo].[PlayerHistory]([Player], [Event])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'PlayerParty')
BEGIN
	CREATE TABLE [dbo].[PlayerParty] (
		[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id]),
		[Character] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Characters]([Id]),
		[InParty] bit NOT NULL,
		[CheckpointDate] datetime NOT NULL
	)
	CREATE CLUSTERED INDEX IX__PlayerParty__Clustered ON [dbo].[PlayerParty]([Player], [Character])
END

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dbo' and t.[name] = 'AreaRoomOnInitialLoad')
	CREATE TABLE [dbo].[AreaRoomOnInitialLoad] (
		[Area] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Areas]([Id]),
		[Room] int NOT NULL FOREIGN KEY REFERENCES [dbo].[Rooms]([Id])
	)

IF NOT EXISTS (SELECT 1 FROM [sys].[tables] t 
			   INNER JOIN [sys].[schemas] s ON (t.[schema_id] = s.[schema_id]) WHERE s.[name] = 'dev' and t.[name] = 'DevPlayers')
	CREATE TABLE [dev].[DevPlayers] (
		[Player] uniqueidentifier NOT NULL FOREIGN KEY REFERENCES [dbo].[Players]([Id])
	)

GO

IF EXISTS (SELECT 1 FROM [sys].[views] WHERE [name] = 'Results')
	DROP VIEW [dev].[Results]
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

IF EXISTS (SELECT 1 FROM [sys].[views] WHERE [name] = 'Messages')
	DROP VIEW [dev].[Messages]
GO	

CREATE VIEW [dev].[Messages] AS
	SELECT m.[Id],
		   ISNULL(mn.[Name], '') AS [Name],
		   m.[Text]
	FROM [dbo].[Messages] m
	LEFT JOIN [dev].[MessageNames] mn
	ON mn.[Message] = m.[Id]
	
GO

IF EXISTS (SELECT 1 FROM [sys].[views] WHERE [name] = 'MessageChoices')
	DROP VIEW [dev].[MessageChoices]
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

IF EXISTS (SELECT 1 FROM [sys].[views] WHERE [name] = 'ActionNames')
	DROP VIEW [dev].[ActionNames]
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

IF EXISTS (SELECT 1 FROM [sys].[views] WHERE [name] = 'ActionResultTypes')
	DROP VIEW [dev].[ActionResultTypes]
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

IF EXISTS (SELECT 1 FROM [sys].[views] WHERE [name] = 'MessageChoiceResultTypes')
	DROP VIEW [dev].[MessageChoiceResultTypes]
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

IF EXISTS (SELECT 1 FROM [sys].[views] WHERE [name] = 'Players')
	DROP VIEW [dev].[Players]
GO	

CREATE VIEW [dev].[Players] AS
	SELECT eun.[UserName] + '@' + edn.[DomainName] + '.' + ed.[Domain] AS [Login],
		   p.[Password],
		   p.[Id],
		   p.[LastCheckpoint]
	FROM [dbo].[Players] p
	INNER JOIN [dbo].[EmailUserNames] eun
	ON p.[EmailUserName] = eun.[Id]
	INNER JOIN [dbo].[EmailDomainNames] edn
	ON p.[EmailDomainName] = edn.[Id]
	INNER JOIN [dbo].[EmailDomains] ed
	ON p.[EmailDomain] = ed.[Id]
	
GO
	