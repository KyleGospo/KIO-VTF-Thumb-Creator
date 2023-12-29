Name:       VTFThumbCreator
Version:    {{{ git_dir_version }}}
Release:    1%{?dist}
Summary:    KIO Thumbnail Creator plugin for Valve Texture Files

License:    GPLv3
URL:        https://github.com/AndrewBetson/KIO-VTF-Thumb-Creator
VCS:        {{{ git_dir_vcs }}}
Source:     {{{ git_dir_pack }}}

Requires:   VTFLib

BuildRequires: cmake
BuildRequires: gcc
BuildRequires: g++
Buildrequires: VTFLib-devel
BuildRequires: pkgconfig(VTFLib)
BuildRequires: qt5-qtbase-devel
BuildRequires: qt5-qttools
BuildRequires: extra-cmake-modules
BuildRequires: kf5-kio-devel
BuildRequires: kf5-kfilemetadata-devel
BuildRequires: shared-mime-info

# Disable debug packages
%define debug_package %{nil}

%description
Plugin for KDE KIO thumbnail to load Valve Texture Files (read-only). Using this you will be able to preview VTF files in KDE programs like Dolphin.

%prep
{{{ git_dir_setup_macro }}}

%build
%cmake -DCMAKE_BUILD_TYPE=Release
%cmake_build

%install
%cmake_install

%files
%license LICENSE.md
%doc README.md
%{_libdir}/qt5/plugins/vtfthumbcreator.so
%{_datadir}/kservices5/vtfthumbcreator.desktop
%{_datadir}/mime/packages/x-vtf.xml
