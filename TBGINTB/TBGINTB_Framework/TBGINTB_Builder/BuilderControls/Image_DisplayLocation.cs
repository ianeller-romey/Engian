using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class Image_DisplayLocation : Image, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS

        readonly string[] c_validImageTypes = { ".png", ".bmp", ".jpg" };

        #endregion


        #region MEMBER PROPERTIES

        public int LocationID { get; private set; }
        public string LocationFile { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Image_DisplayLocation()
        {
            AllowDrop = true;
            Drop += Image_DisplayLocation_Drop;
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.LocationGet += GinTubBuilderManager_LocationGet;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.LocationGet -= GinTubBuilderManager_LocationGet;
        }

        #endregion


        #region Private Functionality

        private void SetLocationImage(int id, string file)
        {
            LocationID = id;
            LocationFile = file;

            Source = new BitmapImage(new Uri(LocationFile));
        }

        private void Image_DisplayLocation_Drop(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
                string file = files.First();
                if(c_validImageTypes.Contains(Path.GetExtension(file)))
                    GinTubBuilderManager.ModifyLocation(LocationID, null, file);
            }
        }

        private void GinTubBuilderManager_LocationGet(object sender, GinTubBuilderManager.LocationGetEventArgs args)
        {
            SetLocationImage(args.Id, args.LocationFile);
        }

        #endregion

        #endregion

    }
}
