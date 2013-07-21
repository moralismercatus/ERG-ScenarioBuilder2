#pragma once
#ifndef MAIN_DIRECTORY_H
#define MAIN_DIRECTORY_H

class MainDirectory
{
public:
    MainDirectory(const QString& dir) :
        maind_(dir),
        srcd_(maind_ + "/src"),
        indexf_(srcd_ + "index.html"),
        webd_(srcd_ + "/web"),
        cssd_(webd_ + "/css"),
        imgd_(webd_ + "/img"),
        jsd_(webd_ + "/js")
    {}

    QString main_dir() { return maind_; }
    QString src_dir() { return srcd_; }
    QString index_file() { return indexf_; }
    QString web_dir() { return webd_; }
    QString css_dir() { return cssd_; }
    QString img_dir() { return imgd_; }
    QString js_dir() { return jsd_; }

private:
    QString maind_;
    QString srcd_;
    QString indexf_;
    QString webd_;
    QString cssd_;
    QString imgd_;
    QString jsd_;
};

#endif // MAIN_DIRECTORY_H
