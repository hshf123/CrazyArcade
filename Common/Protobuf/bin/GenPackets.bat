pushd %~dp0
protoc.exe -I=./ --cpp_out=./ --csharp_out=./ ./Enum.proto
protoc.exe -I=./ --cpp_out=./ --csharp_out=./ ./Struct.proto
protoc.exe -I=./ --cpp_out=./ --csharp_out=./ ./Protocol.proto

GenPackets.exe --path=./Protocol.proto --output=ClientPacketHandler --recv=C_ --send=S_
GenPackets.exe --path=./Protocol.proto --output=ServerPacketHandler --recv=S_ --send=C_
IF ERRORLEVEL 1 PAUSE

XCOPY /Y ENum.pb.h "../../../Server"
XCOPY /Y ENum.pb.cc "../../../Server"
XCOPY /Y Struct.pb.h "../../../Server"
XCOPY /Y Struct.pb.cc "../../../Server"
XCOPY /Y Protocol.pb.h "../../../Server"
XCOPY /Y Protocol.pb.cc "../../../Server"
XCOPY /Y ClientPacketHandler.h "../../../Server"

XCOPY /Y ENum.cs "../../../Client/Assets/@Scripts/Network/Protocol"
XCOPY /Y Struct.cs "../../../Client/Assets/@Scripts/Network/Protocol"
XCOPY /Y Protocol.cs "../../../Client/Assets/@Scripts/Network/Protocol"
XCOPY /Y ServerPacketHandler.cs "../../../Client/Assets/@Scripts/Network/Packet"

DEL /Q /F *pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.h
DEL /Q /F *.cs

PAUSE