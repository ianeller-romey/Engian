using System;
using System.ComponentModel;


namespace TBGINTB_Builder.Lib.Model
{
    public class ObservablePropertiesObject : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        protected void NotifyPropertyChanged(string name)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(name));
            } 
        }
    }
}
