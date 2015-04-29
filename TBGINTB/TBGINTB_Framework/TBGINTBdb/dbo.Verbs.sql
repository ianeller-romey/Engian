CREATE TABLE [dbo].[Verbs]
(
	[Id] INT NOT NULL PRIMARY KEY IDENTITY, 
    [Name] VARCHAR(50) NOT NULL, 
    [Type] INT NOT NULL, 
    CONSTRAINT [FK_Verbs_VerbTypes] FOREIGN KEY ([Type]) REFERENCES [VerbTypes]([Id]) 
)

GO

CREATE INDEX [IX_Verbs_Id] ON [dbo].[Verbs] ([Id])

GO

CREATE INDEX [IX_Verbs_Type] ON [dbo].[Verbs] ([Type])
