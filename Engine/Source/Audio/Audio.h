  /////////////////
 // Audio Class //
/////////////////

// By MCL, w/ the help of kacperks

namespace fr::Audio
{
	class Audio
	{
		private:
			fr::String file;
			int volume;
		
		public:
			Audio(fr::String file);
			Audio(fr::String file, int volume);
		
			void Play();
			void SetVolume();
			void setFilePath(fr::String file);
		
			int GetVolume();
			fr::String GetFile();
	};
}